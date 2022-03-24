
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
#include <list>

#include "Generator.hh"
#include "Exception.hh"

namespace oct::mont
{



Generator::Generator(const Database& db,jup::Jupiter::Lingua l) : database(&db),lingua(l),human_readable(false)
{
}


void Generator::container(const Field& field,const char* name,std::string& result)const
{
	if(human_readable) result += "\n";
	if(name) result += name;
	else result += field.get_type_cstr();
	result += " ";
	result += field.get_name();
	if(field.get_length() != field.type_size())
	{
		unsigned int length;
		length = field.get_length() / field.type_size();
		result += "[";
		result += std::to_string(length);
		result += "]";
	}
	result += ";";
}
void Generator::container(const Table& table,const char* name, std::string& result)const
{
	result += "struct ";
	if(name) result += name;
	else result += table.get_singular();
	if(human_readable) result += "\n";
	result += "{";
	for(const Field& field : table.get_fields())
	{
		container(field,NULL,result);
	}
	if(human_readable) result += "\n";
	result += "};";
}
void Generator::container(const Table& table,const char* name,std::list<const Field*> fields,std::string& result)const
{
	result += "struct ";
	if(name) result += name;
	else result += table.get_singular();
	if(human_readable) result += "\n";
	result += "{";
	for(const Field* field : fields)
	{
		container(*field,NULL,result);
	}
	if(human_readable) result += "\n";
	result += "};";
}
void Generator::container(std::string& result)const
{
	for(const Table& table : database->get_tables())
	{
		result += "\nx";
		container(table,NULL,result);
	}
}





void Generator::container(std::ofstream& result,bool human_readable)const
{
	std::string res;
	
	container(res);
}
void Generator::container(const std::filesystem::path& result)const
{
	std::string res;
	
	container(res);
	
	std::ofstream fres;
	fres.open(result);	
	fres << res;
	fres.flush();
	fres.close();
}
void Generator::container(const char* strtable,const char* name,const std::list<const char*>& strfileds,std::string& result)const
{
	std::list<const Field*> fields;	
	if(not maping_fields(strtable,strfileds,fields)) throw Exception(Exception::FAIL_BUILD_GENERATION,strtable,__FILE__,__LINE__);
	
	const Table* table = database->find(strtable);
	if(not table)throw Exception(Exception::NO_FOUND_TABLE,strtable,__FILE__,__LINE__);
	
	container(*table,name,fields,result);
}
void Generator::container(const char* strtable,const char* name,const std::list<const char*>& strfields,std::ofstream& result) const
{
	std::string res;
	
	const Table* table = database->find(strtable);
	if(not table) throw Exception(Exception::NO_FOUND_TABLE,strtable,__FILE__,__LINE__);
	
	std::list<const Field*> fields;	
	if(not maping_fields(strtable,strfields,fields)) throw Exception(Exception::FAIL_BUILD_GENERATION,strtable,__FILE__,__LINE__);
	
	container(*table,name,fields,res);
}


void Generator::container(const char* strtable,const char* name,const std::list<const char*>& strfields,const std::filesystem::path& result)const
{
	std::string res;
	
	const Table* table = database->find(strtable);
	if(not table)throw Exception(Exception::NO_FOUND_TABLE,strtable,__FILE__,__LINE__);
	
	std::list<const Field*> fields;	
	if(not maping_fields(strtable,strfields,fields)) throw Exception(Exception::FAIL_BUILD_GENERATION,strtable,__FILE__,__LINE__);
	
	container(*table,name,fields,res);
	
	std::ofstream fres;
	fres.open(result);
	fres.flush();
	fres.close();
}

bool Generator::maping_fields(const char* strtable,const std::list<const char*>& strfields,std::list<const Field*>& result)const
{
	const Table* table = database->find(strtable);
	if(not table) throw Exception(Exception::NO_FOUND_TABLE,strtable,__FILE__,__LINE__); 
	if(result.size() != 0) throw Exception(Exception::FAIL_ON_MAPPING_FIEL,__FILE__,__LINE__);
	
	unsigned int i = 0;
	const Field* field;
	for(const char* strfield : strfields)
	{
		field = table->find(strfield);
		if(not field) throw Exception(Exception::NO_FOUND_FIELD,strfield,__FILE__,__LINE__);
		
		result.push_back(field);
	}
	if(strfields.size() != result.size()) throw Exception(Exception::FAIL_ON_MAPPING_FIEL,__FILE__,__LINE__);
	
	return true;
}


void Generator::engine(const Table& table,std::ofstream& result)const
{
	std::list<const Field*> fixed;
	std::list<const Field*> dinamic;
	
	for(const Field& field: table.get_fields())
	{
		if(field.is_fixed())
		{
			fixed.push_back(&field);
		}
		else
		{
			dinamic.push_back(&field);
		}
	}
}
}

