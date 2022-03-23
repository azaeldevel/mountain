
#ifndef OCTETOS_MOUNTAIN_DATABASE_HH
#define OCTETOS_MOUNTAIN_DATABASE_HH

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
#include <libconfig.h++>
#include <string>
#include <octetos/core/Version.hh>
#include <list>
#include <vector>

namespace oct::mont
{
class Field;


typedef unsigned int Index;


class Table
{
public:
	Table();
	Table(const std::filesystem::path&);
	Table(Table&&);

	void load(const std::filesystem::path&);
	/**
	*\brief Busca un campo por nombre
	*\return NULL si no lo encuenatr, o el puntero conrespodiente si lo encuentra
	*/
	const Field* find(const char*)const;
	
	const char* get_name()const;
	const char* get_singular()const;
	Index get_length()const;
	const std::vector<Field>& get_fields()const;
	
private:
	std::string name;
	std::string singular;
	Index length;
	std::vector<Field> fields;
};

class Field
{
friend void Table::load(const std::filesystem::path&);
public:
	enum Type
	{
		NONE,
		BOOL,/*1*/
		CHAR,/*2*/
		SHORT,/*3*/
		UNSIGNED_SHORT,/*4*/
		INT,/*5*/
		UNSIGNED_INT,/*6*/
		FLOAT,/*7*/
	};
	static const char* type_cstr(Type);
	static Index type_size(Type);
	/**
	*\brief determina si el tamano del campo length puede ser deducido a parter de type, solo un campo char es variable
	*/
	//static bool is_fixed(Type);
public:
	Field(const std::filesystem::path&);
	Field();

	const char* get_name()const;
	Type get_type()const;
	const char* get_type_cstr()const;
	Index get_length()const;
	bool get_pk()const;
	/**
	*\brief valor valido solo si pk es true, en otro caso su valor no es incicializado
	*\return true si se activa el auto incremento de la llave priamria, falso en otro caso
	*/
	bool get_auto_inc()const;

	void load(const std::filesystem::path&);

private:
	std::string name;
	Type type;
	Index length;
	bool pk;
	
	bool auto_inc;//auto incrementto de primary key
};

class Database
{
public:
	Database(const std::filesystem::path&);

	const oct::core::Semver& get_version()const;
	const char* get_name()const;
	const std::vector<Table>& get_tables()const;
	Index get_length()const;

	void load(const std::filesystem::path&);
	const Table* find(const char*)const;
private:
	oct::core::Semver version;
	std::string name;
	std::vector<Table> tables;
	Index length;
};


}

#endif
