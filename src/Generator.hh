

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


#include "Database.hh"


namespace oct::mont
{

class Generator
{
public:
	Generator(const Database& db);
	/**
	*\brief Genera contenedor para los campos especificados
	*\param table nombre de la table
	*\param fileds nombres de los campos
	*\param result variable donde se coloca el resutado
	*\param human_readable true para usar una notacion indentada, false usara notacion mas eficiente para la manipuacion del sistema
	*/
	bool build(const char* table,const std::vector<const char*>& fileds,const char* name,std::string& result,bool human_readable);	
	bool build(const char* table,const std::vector<const char*>& fileds,const char* name,std::ofstream& result,bool human_readable);
	bool build(const char* table,const std::vector<const char*>& fileds,const char* name,std::filesystem::path& result,bool human_readable);
	
private:
	/**
	*\brief Mapea el nombre del campo con el objeto Field
	*
	*/
	bool maping_fields(const char*,const std::vector<const char*>&,std::vector<const Field*>& result);

private:
	const Database* const database;
};

}


#endif