
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
#include <fstream>


#include "Generator.hh"
#include "Exception.hh"

namespace oct::mont
{



Generator::Generator(const Database& db) : database(&db)
{
}


	
bool Generator::build(std::string& result,bool human_readable)
{
	for(const Table& table : database->get_tables())
	{
		result += "\nstruct ";
		result += table.get_singular();
		if(human_readable) result += "\n";
		result += "{";
		for(const Field& field : table.get_fields())
		{
			if(human_readable) result += "\n";
			result += field.get_type_cstr();
			result += " ";
			result += field.get_name();
			if(field.get_length() != Field::type_size(field.get_type()))
			{
				unsigned int length;
				length = field.get_length() / Field::type_size(field.get_type());
				result += "[";
				result += std::to_string(length);
				result += "]";
			}
			result += ";";
		}		
		if(human_readable) result += "\n";
		result += "};";
	}
	
	return true;
}
bool Generator::build(std::ofstream& result,bool human_readable)
{
	std::string res;
	
	bool ret = build(res,human_readable);
	if(not ret) throw Exception(Exception::FAIL_BUILD_GENERATION,__FILE__,__LINE__);
	
	result << "\n" << res;
	
	return true;
}
bool Generator::build(const std::filesystem::path& result,bool human_readable)
{
	std::string res;
	
	bool ret = build(res,human_readable);
	if(not ret) throw Exception(Exception::FAIL_BUILD_GENERATION,__FILE__,__LINE__);
	
	std::ofstream fres;
	fres.open(result);	
	fres << res;
	fres.flush();
	fres.close();
	
	return true;
}

bool Generator::build(const char* table,const std::vector<const char*>& strfileds,const char* name,std::string& result,bool human_readable)
{
	std::vector<const Field*> fields;
	
	if(not maping_fields(table,strfileds,fields)) throw Exception(Exception::FAIL_BUILD_GENERATION,table,__FILE__,__LINE__);
	
	result = "struct ";
	result += name;
	if(human_readable) result += "\n";
	result += "{";
	for(unsigned int i = 0; i < fields.size(); i++)
	{
		if(not fields[i]) throw Exception(Exception::FAIL_BUILD_GENERATION,table,__FILE__,__LINE__);
		
		if(human_readable) result += "\n";
		result += fields[i]->get_type_cstr();
		result += " ";
		result += fields[i]->get_name();
		if(fields[i]->get_length() != Field::type_size(fields[i]->get_type()))
		{
			unsigned int length;
			length = fields[i]->get_length() / Field::type_size(fields[i]->get_type());
			result += "[";
			result += std::to_string(length);
			result += "]";
		}
		result += ";";		
	}
	if(human_readable) result += "\n";
	result += "};";
	
	return true; 
}
bool Generator::build(const char* table,const std::vector<const char*>& fields,const char* name,std::ofstream& result,bool human_readable)
{
	std::string res;
	
	bool ret = build(table,fields,name,res,human_readable);
	if(not ret) throw Exception(Exception::FAIL_BUILD_GENERATION,table,__FILE__,__LINE__);
	
	result << "\n" << res;
	
	return true;
}


bool Generator::build(const char* table,const std::vector<const char*>& fields,const char* name,const std::filesystem::path& result,bool human_readable)
{
	std::string res;
	
	bool ret = build(table,fields,name,res,human_readable);
	if(not ret) throw Exception(Exception::FAIL_BUILD_GENERATION,table,__FILE__,__LINE__);
	
	std::ofstream fres;
	fres.open(result);	
	fres << "\n" << res;
	fres.flush();
	fres.close();
	
	return true;
}

bool Generator::maping_fields(const char* strtable,const std::vector<const char*>& strfields,std::vector<const Field*>& result)
{
	const Table* table = database->find(strtable);
	if(not table) throw Exception(Exception::NO_FOUND_TABLE,strtable,__FILE__,__LINE__); 
	
	std::vector<const Field*> fields(strfields.size());	
	unsigned int i = 0;
	const Field* field;
	if(result.size() != strfields.size()) result.resize(strfields.size());
	for(const char* strfield : strfields)
	{
		field = table->find(strfield);
		if(not field) throw Exception(Exception::NO_FOUND_FIELD,strfield,__FILE__,__LINE__);
		
		result[i] = field;
		
		i++;
	}
	if(i != result.size()) throw Exception(Exception::FAIL_ON_MAPPING_FIEL,__FILE__,__LINE__);
	
	return true;
}

}

