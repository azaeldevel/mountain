

#ifndef OCTETOS_MOUNTAIN_GENERATOR_HH
#define OCTETOS_MOUNTAIN_GENERATOR_HH

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

#include "Jupiter.hh"
#include "Database.hh"


namespace oct::mont
{

struct field_alias
{
	const char* field;
	const char* alias;
};


class Generator
{
public:
	Generator(const Database& db,jup::Jupiter::Lingua);
	

	
	void container(const Field&,const char* name,std::string& result)const;
	void container(const Table&,const char* name,std::string& result)const;
	void container(std::string& result)const;
	
	void container(std::ofstream& result,bool human_readable)const;
	void container(const std::filesystem::path& result)const;

	void container(const Table&,const char* name,std::list<const Field*>,std::string& result)const;
	/**
	*\brief Genera contenedor para los campos especificados
	*\param table nombre de la table
	*\param fileds nombres de los campos
	*\param result variable donde se coloca el resutado
	*\param human_readable true para usar una notacion indentada, false usara notacion mas eficiente para la manipuacion del sistema
	*/
	void container(const char* table,const char* name,const std::list<const char*>& fileds,std::string& result)const;	
	void container(const char* table,const char* name,const std::list<const char*>& fileds,std::ofstream& result)const;
	void container(const char* table,const char* name,const std::list<const char*>& fileds,const std::filesystem::path& result)const;
	

	/**
	*\brief Genera un motaor de acceso para la tabla indicada
	*\param table nombre de la table
	*/
	void engine(const Table&,std::ofstream& result)const;
	void engine(const char* table,const char* name,const std::list<const char*>& fileds,std::string& result,bool human_readable)const;

private:

	/**
	*\brief Mapea el nombre del campo con el objeto Field
	*/
	bool maping_fields(const char*,const std::list<const char*>&,std::list<const Field*>& result)const;
public:
	bool human_readable;
	std::string prefix;
private:
	const Database* const database;
	jup::Jupiter::Lingua lingua;
	std::string prefix_name_file;
	std::filesystem::path header;
	std::filesystem::path source;
};

}


#endif