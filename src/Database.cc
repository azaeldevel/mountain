
#include <iostream>


#include "Exception.hh"
#include "Database.hh"

namespace oct::mont
{



Field::Field(Field&& field)
{
}

Field::Field(const std::filesystem::path& tb)
{
	load(tb);
}

void Field::load(const std::filesystem::path& table)
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
std::list<Table>& Database::get_tables()
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