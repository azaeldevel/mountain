

#ifndef OCTETOS_MOUNTAIN_DATABASE_HH
#define OCTETOS_MOUNTAIN_DATABASE_HH

#include <filesystem>
#include <libconfig.h++>
#include <string>
#include <octetos/core/Version.hh>
#include <list>

namespace oct::mont
{
typedef unsigned int Index;

class Field
{

public:
	Field(const std::filesystem::path&);
	Field(Field&&);

	const char* get_name()const;

	void load(const std::filesystem::path&);

private:
	std::string name;

};
class Table
{
public:
	Table(const std::filesystem::path&);
	Table(Table&&);

	void load(const std::filesystem::path&);
	
	const char* get_name()const;
	const char* get_singular()const;
	Index get_length()const;
	
private:
	std::string name;
	std::string singular;
	Index length;
};

class Database
{
public:
	Database(const std::filesystem::path&);

	const oct::core::Semver& get_version()const;
	const char* get_name()const;
	std::list<Table>& get_tables();
	Index get_length()const;

	void load(const std::filesystem::path&);
private:
	oct::core::Semver version;
	std::string name;
	std::list<Table> tables;
	Index length;
};


}

#endif
