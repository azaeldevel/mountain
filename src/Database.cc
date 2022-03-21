
#include <iostream>


#include "Database.hh"

namespace oct::mont
{

Table::Table(Table&& table) : name(std::move(table.name))
{
}

Table::Table(const std::filesystem::path& tb)
{
	load(tb);
}

void Table::load(const std::filesystem::path& table)
{
	name = table.filename().string();
	
	std::filesystem::path table_header = table / ".table";
	
	//libconfig::Config config;
	//config.readFile(table_header.string().c_str());
	
	//name = (const char*)config.lookup("name");
}
	
const char* Table::get_name()const
{
	return name.c_str();
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
	libconfig::Config config;
	std::filesystem::path db_header = db / ".db";
	config.readFile(db_header.string().c_str());
	
	
	version.set(config.lookup("version"));
	
	name = (const char*)config.lookup("name");
	
	
	//load tables
	for (auto const& dir_entry : std::filesystem::directory_iterator{db})
	{
		if(std::filesystem::is_directory(dir_entry)) 
		{
			//std::cout << "dir : " << dir_entry << "\n";
			tables.push_back(Table(dir_entry));
		}
	}
	
	
}

}