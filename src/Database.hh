

#ifndef OCTETOS_MOUNTAIN_DATABASE_HH
#define OCTETOS_MOUNTAIN_DATABASE_HH

#include <filesystem>
#include <libconfig.h++>
#include <string>
#include <octetos/core/Version.hh>
#include <list>

namespace oct::mont
{
class Field;


typedef unsigned int Index;


class Table
{
public:
	Table(const std::filesystem::path&);
	Table(Table&&);

	void load(const std::filesystem::path&);
	
	const char* get_name()const;
	const char* get_singular()const;
	Index get_length()const;
	const std::list<Field>& get_fields()const;
	
private:
	std::string name;
	std::string singular;
	Index length;
	std::list<Field> fields;
};

class Field
{
friend void Table::load(const std::filesystem::path&);
public:
	Field(const std::filesystem::path&);
	Field();

	const char* get_name()const;
	const char* get_type()const;

	void load(const std::filesystem::path&);

private:
	std::string name;
	std::string type;
	Index length;
	bool pk;

};

class Database
{
public:
	Database(const std::filesystem::path&);

	const oct::core::Semver& get_version()const;
	const char* get_name()const;
	const std::list<Table>& get_tables()const;
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
