

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

void Database::load(const std::filesystem::path& db)
{
	libconfig::Config config;
	std::filesystem::path db_header = db / ".db";
	config.readFile(db_header.string().c_str());
	
	
	version.set(config.lookup("version"));
	
	name = (const char*)config.lookup("name");
	
	
}

}