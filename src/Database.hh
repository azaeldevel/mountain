

#ifndef OCTETOS_MOUNTAIN_DATABASE_HH
#define OCTETOS_MOUNTAIN_DATABASE_HH

#include <filesystem>
#include <libconfig.h++>
#include <string>
#include <octetos/core/Version.hh>
#include <list>

namespace oct::mont
{

class Table
{
public:
	Table(const std::filesystem::path&);
	Table(Table&&);

	void load(const std::filesystem::path&);
	
	const char* get_name()const;
	
private:
	std::string name;
};

class Database
{
public:
	Database(const std::filesystem::path&);

	const oct::core::Semver& get_version()const;
	const char* get_name()const;
	std::list<Table>& get_tables();

	void load(const std::filesystem::path&);
private:
	oct::core::Semver version;
	std::string name;
	std::list<Table> tables;

};


}

#endif
