
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







}

