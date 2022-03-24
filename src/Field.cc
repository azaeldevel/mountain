
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

#include "Exception.hh"
#include "Database.hh"

namespace oct::mont
{


const char* Field::type_cstr(Type type)
{
	switch(type)
	{
	case Type::NONE:
		throw Exception(Exception::NOT_SET_TYPE_FIELD,__FILE__,__LINE__);
	case Type::BOOL:
		return "bool";
	case Type::CHAR:
		return "char";
	case Type::SHORT:
		return "short";
	case Type::UNSIGNED_SHORT:
		return "unsigned short";
	case Type::INT:
		return "int";
	case Type::UNSIGNED_INT:
		return "unsigned int";
	case Type::FLOAT:
		return "float";
	default:
		throw Exception(Exception::UNKNOW_TYPE_FIELD,__FILE__,__LINE__);
	}
	
	throw Exception(Exception::UNKNOW_TYPE_FIELD,__FILE__,__LINE__);
}
Index Field::type_size(Type type)
{
	switch(type)
	{
	case Type::NONE:
		throw Exception(Exception::NOT_SET_TYPE_FIELD,__FILE__,__LINE__);
	case Type::BOOL:
		return sizeof(bool);
	case Type::CHAR:
		return sizeof(char);
	case Type::SHORT:
		return sizeof(short);
	case Type::UNSIGNED_SHORT:
		return sizeof(unsigned short);
	case Type::INT:
		return sizeof(int);
	case Type::UNSIGNED_INT:
		return sizeof(unsigned int);
	case Type::FLOAT:
		return sizeof(float);
	default:
		throw Exception(Exception::UNKNOW_TYPE_FIELD,__FILE__,__LINE__);
	}
	
	return 0;
}
bool Field::is_fixed(Type type)
{
	switch(type)
	{
	case Type::NONE:
		throw Exception(Exception::NOT_SET_TYPE_FIELD,__FILE__,__LINE__);
	case Type::BOOL:
	case Type::CHAR:
	case Type::SHORT:
	case Type::UNSIGNED_SHORT:
	case Type::INT:
	case Type::UNSIGNED_INT:
	case Type::FLOAT:
		return true;
	case Type::STRING:
		return false;
	default:
		throw Exception(Exception::UNKNOW_TYPE_FIELD,__FILE__,__LINE__);
	}
	
	throw Exception(Exception::UNKNOW_TYPE_FIELD,__FILE__,__LINE__);
}
Field::Field() : length(0)
{
}
const char* Field::get_name()const
{
	return name.c_str();
}
Field::Type Field::get_type()const
{
	return type;
}
const char* Field::get_type_cstr()const
{
	return type_cstr(type);
}
Index Field::get_length()const
{
	return length;
}
bool Field::get_pk()const
{
	return pk;
}
bool Field::get_auto_inc()const
{
	return auto_inc;
}
Field::Field(const std::filesystem::path& tb)
{
	load(tb);
}

void Field::load(const std::filesystem::path& field)
{
	/*if(not std::filesystem::exists(table)) throw Exception(Exception::NO_EXISTS_TB,__FILE__,__LINE__);
	
	name = table.filename().string();	
	std::filesystem::path table_header = table / ".table";
	if(not std::filesystem::exists(table_header)) throw Exception(Exception::NO_EXISTS_HEADER_TB,__FILE__,__LINE__);
	
	libconfig::Config config;
	//std::cout << "table_header : " << table_header << "\n";
	config.readFile(table_header);
	
	singular = (const char*)config.lookup("singular");	
	config.lookupValue("length",length);*/
}




}