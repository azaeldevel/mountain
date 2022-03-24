
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

#include <fstream>

#include "Jupiter.hh"


namespace oct::jup
{


	
Exception::Exception()
{
}
Exception::Exception(unsigned int c) : core::v3::Exception(c)
{
}
Exception::Exception(unsigned int c,const char* s) : core::v3::Exception(c,s)
{
}
Exception::Exception(unsigned int c,const char* f, unsigned int l) : core::v3::Exception(c,f,l)
{
}
Exception::Exception(unsigned int c,const char* s,const char* f, unsigned int l) : core::v3::Exception(c,s,f,l)
{
}


const char* Exception::what () const throw ()
{
	switch(code())
	{
	case Errors::NO_ERROR:
		return "No error";
	case Errors::NOT_SET_TYPE_PROJECT:
		return "Se se ha indicado el tipo de projecto";
	case Errors::UNKNOW_TYPE_PROJECT:
		return "Se deconoce le tipo de projecto especificado";
	case Errors::NOT_SET_LINGUA_PROJECT:
		return "No se ha indicado el lenguaje del projecto";
	case Errors::UNKNOW_NAME_PROJECT:
		return "No se ha indicado el nombre del proyecto";
	default:
		return "Error desconocido";
	}
	return "Error desconocido";
}









bool Jupiter::generate() const
{	
	switch(type)
	{
	case Type::None:
		throw Exception(Exception::NOT_SET_TYPE_PROJECT,__FILE__,__LINE__);
	case Type::Autotools:
		return generate_autotools();
	default:
		throw Exception(Exception::UNKNOW_TYPE_PROJECT,__FILE__,__LINE__);
	}

	return false;
}
bool Jupiter::generate_autotools() const
{
	switch(lingua)
	{
	case Lingua::None:
		throw Exception(Exception::NOT_SET_LINGUA_PROJECT,__FILE__,__LINE__);
	case Lingua::CC:
		return generate_autotools_cc();
	default:
		throw Exception(Exception::UNKNOW_TYPE_PROJECT,__FILE__,__LINE__);
	}

	return false;
}

bool Jupiter::generate_autotools_cc() const
{
	if(not std::filesystem::exists(directory)) std::filesystem::create_directory(directory);
	
	std::filesystem::path actual_path;
	std::ofstream actual_file;
	
	actual_path = directory/"configure.ac";
	actual_file.open(actual_path);
	
	if(name.empty()) throw Exception(Exception::UNKNOW_NAME_PROJECT,__FILE__,__LINE__);
	actual_file << "AC_INIT(" << name;
	if(version.getMajor() >= 0 and version.getMinor() >= 0) actual_file << "," << (std::string)version;
	if(not maintenance.empty()) actual_file << "," << maintenance ;
	actual_file << ")";
	actual_file << "\n";
	actual_file << "AC_CONFIG_HEADERS([config.h]";
	actual_file << "\n";
	actual_file << "AM_INIT_AUTOMAKE([1.11])";
	actual_file << "\n";
	actual_file << "AM_SILENT_RULES([yes])";
	actual_file << "\n";
	actual_file << "AC_PROG_CXX";
	actual_file << "\n";
	actual_file << "LT_INIT\n";
	
	actual_file << "PKG_CHECK_MODULES(SATURNO,octetos-saturno)\n";
	
	actual_file << "AC_OUTPUT([";
	actual_file << "Makefile";
	actual_file << " src/Makefile";
	actual_file << "])";
	
	actual_file.flush();
	actual_file.close();
	
	actual_path = directory/"Makefile.am";
	actual_file.open(actual_path);
	
	actual_file << "SUBDIRS = src";
	actual_file << "\n\n";	
	actual_file << "uninstall-local: \n";
	actual_file << "\t-rm -r $(docdir)\n";
	
	actual_file.flush();
	actual_file.close();
	
	actual_path = directory/"src";
	if(not std::filesystem::exists(actual_path)) create_directory(actual_path);
	
	
	actual_path = directory/"src/Makefile.am";
	actual_file.open(actual_path);
	
	std::string target_file = "lib" + name + ".la";
	std::string target_auto = "lib" + name + "_la";
	//target += ;
	actual_file << "AM_CFLAGS = -Wall\n\n";
	actual_file << "lib_LTLIBRARIES = " << target_file << "\n";
	actual_file << target_auto << "_CXXFLAGS = $(SATURNO_CFLGAS)\n";
	actual_file << target_auto << "_LIBADD = $(SATURNO_LIBS)\n";
	
	std::string source = prefix_source.empty()? name : prefix_source;
	
	actual_file << target_auto << "_SOURCES = " << source << ".cc\n";
	
	
	actual_file.flush();
	actual_file.close();
	
	return true;
}

} 
 