
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

#include <list>
#include <fstream>

#include "Generator.hh"
#include "Exception.hh"

namespace oct::mont
{



Generator::Generator(const Database& db,jup::Jupiter::Lingua l) : database(&db),lingua(l),human_readable(false)
{
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


void Generator::indexs(const Table& table, std::ofstream& result)const
{
	unsigned int count_index;
	//index
	count_index = 0;
	std::string res;
	
	for(const Field& field : table.get_fields())
	{
		if(field.is_index()) 
		{
			count_index++;	
			container(field,NULL,res);		
		}
	}
	if(count_index > 0)
	{
		result << "struct " << table.get_singular() << "_index";
		if(human_readable) result << "\n{\n";
		else result << "{";
		result << res;
		if(count_index > 1) throw Exception(Exception::FAIL_GENERATION_ENGINE_MULTKEY,__FILE__,__LINE__);
		if(human_readable) result << "\n};";
		else result << "};";
	}
	
	
	//primary key
	count_index = 0;
	for(const Field& field : table.get_fields())
	{
		if(field.is_pk()) 
		{
			count_index++;
			container(field,NULL,res);		
		}
	}
	if(count_index > 0)
	{
		result << "struct " << table.get_singular() << "_primary";
		if(human_readable) result << "\n{\n";
		else result << "{";
		result << res;
		if(count_index > 1) throw Exception(Exception::FAIL_GENERATION_ENGINE_MULTKEY,__FILE__,__LINE__);
		if(human_readable) result << "\n};";
		else result << "};";
	}
	
	//foreing key
	
}




}

