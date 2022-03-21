

#include "Exception.hh"
#include "Database.hh"

namespace oct::mont
{


const char* Field::type_cstr(Type type)
{
	switch(type)
	{
	case Field::BOOL:
		return "bool";
	case Field::CHAR:
		return "char";
	case Field::SHORT:
		return "short";
	case Field::UNSIGNED_SHORT:
		return "unsigned short";
	case Field::INT:
		return "int";
	case Field::UNSIGNED_INT:
		return "unsigned int";
	case Field::FLOAT:
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
	case Field::BOOL:
		return sizeof(bool);
	case Field::CHAR:
		return sizeof(char);
	case Field::SHORT:
		return sizeof(short);
	case Field::UNSIGNED_SHORT:
		return sizeof(unsigned short);
	case Field::INT:
		return sizeof(int);
	case Field::UNSIGNED_INT:
		return sizeof(unsigned int);
	case Field::FLOAT:
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
	case Field::BOOL:
	case Field::CHAR:
	case Field::SHORT:
	case Field::UNSIGNED_SHORT:
	case Field::INT:
	case Field::UNSIGNED_INT:
	case Field::FLOAT:
		return true;
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