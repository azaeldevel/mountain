

#ifndef OCTETOS_MOUNTAIN_DATABASE_HH
#define OCTETOS_MOUNTAIN_DATABASE_HH

#include <filesystem>
#include <libconfig.h++>
#include <string>
#include <octetos/core/Version.hh>

namespace oct::mont
{

class Database
{
public:
	Database(const std::filesystem::path&);

	const oct::core::Semver& get_version()const;
	const char* get_name()const;

	void load(const std::filesystem::path&);
private:
	oct::core::Semver version;
	std::string name;
};


}

#endif
