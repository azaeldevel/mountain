
/*
 * Copyright (C) 2022 Azael R. <azael.devel@gmail.com>
 * 
 * mountain is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * mountain is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#include <iostream>
#include <string.h>


#include "Exception.hh"
#include "Database.hh"

namespace oct::mont
{



Table::Table() : length(0)
{
}
Table::Table(Table&& table) : name(std::move(table.name)),length(table.length)
{
}

Table::Table(const std::filesystem::path& tb)
{
	load(tb);
}

void Table::load(const std::filesystem::path& table)
{
	if(not std::filesystem::exists(table)) throw Exception(Exception::NO_EXISTS_TB,__FILE__,__LINE__);
	
	
	//std::cout << "\tTable file: " << table << std::endl;
	name = table.filename().string();
	//std::cout << "\tTable : " << name << std::endl;
	std::filesystem::path table_header = table / ".table";
	//std::cout << "\tTable : " << name << std::endl;
	//std::cout << "table_header : " << table_header << "\n";
	if(not std::filesystem::exists(table_header)) throw Exception(Exception::NO_EXISTS_HEADER_TB,__FILE__,__LINE__);
	
	libconfig::Config config;
	//std::cout << "table_header : " << table_header << "\n";
	config.readFile(table_header);
	
	singular = (const char*)config.lookup("singular");
	const libconfig::Setting& root = config.getRoot();
	length = root["fields"].getLength();
	//std::cout << "\tTable : " << name << ", size req : " << length << std::endl;	
	fields.resize(length);
	Index i_field = 0;
	//Index count_fileds = 0;
	if(not config.exists("fields")) throw Exception(Exception::NO_EXISTS_FIELDS_INFO,__FILE__,__LINE__);
	if(not root["fields"].isList()) throw Exception(Exception::FAILED_FIELD_INFO_FORMAT_FIELD,__FILE__,__LINE__);
	for(const libconfig::Setting& field : root["fields"])
	{	
		//std::cout << "\t\tField" << std::endl;	
		//std::cout << "\tField name : " << (*field).getName() << std::endl;
		if(not field.isGroup()) throw Exception(Exception::FAILED_FIELD_INFO_FORMAT_FIELD_CONTENT,__FILE__,__LINE__);
		
		//count_fileds++;
		//std::cout << "\tField : " << count_fileds << std::endl;
		//std::cout << "\tTable : " << name << ", size : " << fields.size() << std::endl;
		//std::cout << "\ttext : " << (*field).c_str() << std::endl;
		
		
		if(field.exists("name")) 
		{			
			fields[i_field].name = (const char*)field.lookup("name");
			//std::cout << "\t\t" << fields[i_field].name << std::endl;
		}
		else
		{
			throw Exception(Exception::NOT_FOUND_FIELD_NAME,__FILE__,__LINE__);
		}
		if(field.exists("type")) 
		{
			fields[i_field].type = (Field::Type)(int)field.lookup("type");
			//std::cout << "\t\ttype : " << fields[i_field].type << std::endl;
		}
		else
		{
			throw Exception(Exception::NOT_FOUND_FIELD_TYPE,__FILE__,__LINE__);
		}
		if(field.exists("length")) 
		{
			fields[i_field].length = ((Index)(unsigned int)field.lookup("length")) * Field::type_size(fields[i_field].type);
		}
		else
		{
			fields[i_field].length = Field::type_size(fields[i_field].type);		
		}
		if(field.exists("pk")) 
		{
			 field.lookupValue("pk",fields[i_field].pk);
			if(field.exists("auto_inc")) 
			{
				 field.lookupValue("auto_inc",fields[i_field].auto_inc);
			}
			else
			{
				fields[i_field].auto_inc = false;
			}
		}
		else
		{
			fields[i_field].pk = false;
		}
		
		i_field++;
	}
}
const Field* Table::find(const char* name)const
{
	for(const Field& field : fields)
	{
		if(strcmp(field.get_name(), name) == 0) return &field;
	}
	
	return NULL;
}
const char* Table::get_name()const
{
	return name.c_str();
}
const char* Table::get_singular()const
{
	return singular.c_str();
}
Index Table::get_length()const
{
	return fields.size();
}

const std::vector<Field>& Table::get_fields()const
{
	return fields;
}



}