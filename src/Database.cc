
#include <iostream>
#include <string.h>


#include "Exception.hh"
#include "Database.hh"

namespace oct::mont
{



Field::Field() : length(0)
{
}
const char* Field::get_name()const
{
	return name.c_str();
}
const char* Field::get_type()const
{
	return type.c_str();
}

Field::Field(const std::filesystem::path& tb)
{
	load(tb);
}

void Field::load(const std::filesystem::path& field)
{
	/*if(not std::filesystem::exists(table)) throw Exception(Exception::NO_EXISTS_TB,__FILE__,__LINE__);
	
	name = table.filename().string();	
	std::filesystem::path table_header = table / ".table";
	if(not std::filesystem::exists(table_header)) throw Exception(Exception::NO_EXISTS_HEADER_TB,__FILE__,__LINE__);
	
	libconfig::Config config;
	//std::cout << "table_header : " << table_header << "\n";
	config.readFile(table_header);
	
	singular = (const char*)config.lookup("singular");	
	config.lookupValue("length",length);*/
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
	
	name = table.filename().string();	
	std::filesystem::path table_header = table / ".table";
	if(not std::filesystem::exists(table_header)) throw Exception(Exception::NO_EXISTS_HEADER_TB,__FILE__,__LINE__);
	
	libconfig::Config config;
	//std::cout << "table_header : " << table_header << "\n";
	config.readFile(table_header);
	
	singular = (const char*)config.lookup("singular");
	const libconfig::Setting& root = config.getRoot();
	length = root["fields"].getLength();
	Field* temp_field;
	Index count_fileds = 0;
	if(not config.exists("fields")) throw Exception(Exception::NO_EXISTS_FIELDS_INFO,__FILE__,__LINE__);
	if(not root["fields"].isList()) throw Exception(Exception::FAILED_FIELD_INFO_FORMAT_FIELD,__FILE__,__LINE__);
	for(const libconfig::Setting& field : root["fields"])
	{	
		//std::cout << "\t\tField" << std::endl;	
		//std::cout << "\tField name : " << (*field).getName() << std::endl;
		if(not field.isGroup()) throw Exception(Exception::FAILED_FIELD_INFO_FORMAT_FIELD_CONTENT,__FILE__,__LINE__);
		
		count_fileds++;
		//std::cout << "\tField : " << count_fileds << std::endl;
		fields.push_back(Field());
		temp_field = &fields.back();
		//std::cout << "\ttext : " << (*field).c_str() << std::endl;
		if(field.exists("name")) 
		{			
			temp_field->name = (const char*)field.lookup("name");
			//std::cout << "\tField found : " << temp_field->name << std::endl;
		}
		else
		{
			throw Exception(Exception::NOT_FOUND_FIELD_NAME,__FILE__,__LINE__);
		}
		if(field.exists("type")) 
		{
			temp_field->type = (const char*)field.lookup("type");
			//std::cout << "\tField found : " << temp_field->type << std::endl;
		}
		else
		{
			throw Exception(Exception::NOT_FOUND_FIELD_TYPE,__FILE__,__LINE__);
		}
		if(field.exists("pk")) 
		{
			temp_field->pk = field.lookup("pk");
			//std::cout << "\tField found : " << temp_field->type << std::endl;
		}
		else
		{
			temp_field->pk = false;
		}
	}
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
	return length;
}

const std::list<Field>& Table::get_fields()const
{
	return fields;
}
	
	
Database::Database(const std::filesystem::path& db)
{
	load(db);
}

const oct::core::Semver& Database::get_version()const
{
	return version;
}
const char* Database::get_name() const
{
	return name.c_str();
}
const std::list<Table>& Database::get_tables() const
{
	return tables;
}

void Database::load(const std::filesystem::path& db)
{
	if(not std::filesystem::exists(db)) throw Exception(Exception::NO_EXISTS_DB,__FILE__,__LINE__);
	
	std::filesystem::path db_header = db / ".db";
	if(not std::filesystem::exists(db_header)) throw Exception(Exception::NO_EXISTS_HEADER_DB,__FILE__,__LINE__);
	
	libconfig::Config config;
	config.readFile(db_header);
	version.set(config.lookup("version"));
	name = (const char*)config.lookup("name");
	config.lookupValue("length",length);
	
	Index count_tables = 0;
	
	//load tables
	for (auto const& dir_entry : std::filesystem::directory_iterator{db})
	{
		if(std::filesystem::is_directory(dir_entry)) 
		{
			//std::cout << "dir : " << dir_entry << "\n";
			count_tables++;
			tables.push_back(Table(dir_entry));
		}
	}
	
	if(count_tables != tables.size()) throw Exception(Exception::NO_CORRUPT_DB_COUNT_TB,__FILE__,__LINE__);
	
}

}