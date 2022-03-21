
#include <iostream>
#include <string.h>


#include "Exception.hh"
#include "Database.hh"

namespace oct::mont
{







	

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
const std::vector<Table>& Database::get_tables() const
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
	length = config.lookup("length");
	//std::cout << "Database : " << name << ",req size : " << length << "\n";
	tables.resize(length);
	
	//Index count_tables = 0;
	
	//load tables
	Index i_dir_entry = 0;
	for (auto const& dir_entry : std::filesystem::directory_iterator{db})
	{
		if(std::filesystem::is_directory(dir_entry)) 
		{
			//std::cout << "dir : " << dir_entry << "\n";
			tables[i_dir_entry].load(dir_entry);
			i_dir_entry++;
		}
	}
	
	if(i_dir_entry != tables.size()) throw Exception(Exception::NO_CORRUPT_DB_COUNT_TB,__FILE__,__LINE__);
	
}

}