
#ifndef OCTETOS_JUPITER_HH
#define OCTETOS_JUPITER_HH

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

#include <filesystem>
#include <vector>
#include <list>

#include <octetos/core/Exception.hh>
#include <octetos/core/Version.hh>


namespace oct::jup
{

class Exception : public core::v3::Exception
{
public:
	enum Errors
	{
		NO_ERROR,
		NOT_SET_TYPE_PROJECT,
		UNKNOW_TYPE_PROJECT,
		NOT_SET_LINGUA_PROJECT,
		UNKNOW_NAME_PROJECT,
	};
	
public:
	Exception();
	Exception(unsigned int code);
	Exception(unsigned int code,const char* subject);
	Exception(unsigned int code,const char* filename, unsigned int line);
	Exception(unsigned int code,const char* subject,const char* filename, unsigned int line);

	virtual const char* what () const throw ();
};

class Jupiter
{
public:
	enum class Type
	{
		None,
		Autotools,
		CMake,
	};
	enum class Component
	{
		None,
		Library,
		Executable
	};
	enum class Lingua
	{
		None,
		C,
		CC,
		Java,
		Python,
	};
	enum class License
	{
		None,
		GPL,
		OGL,
	};
	enum class Model
	{
		None,
		Consele,
		GTK,
		Mountain,
		Costume,
	};

public:
	bool generate()const;

private:
	bool generate_autotools() const;
	bool generate_autotools_cc() const;
	
public:
	Type type;
	Component component;
	Lingua lingua;

	std::filesystem::path directory;
	std::string name;
	std::string maintenance;
	core::Semver version;
	std::vector<std::filesystem::path> files;
	Model model;
	std::string prefix_source;

	std::list<std::string> authors;
private:
	
};

}

#endif