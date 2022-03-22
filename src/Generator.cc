
#include "Generator.hh"
#include "Exception.hh"

namespace oct::mont
{



Generator::Generator(const Database& db) : database(&db)
{
}

void Generator::maping_fields(const char* strtable,const std::vector<char*>& strfields)
{
	const Table* table = database->find(strtable);
	if(not table) throw Exception(Exception::NO_FOUND_TABLE,strtable,__FILE__,__LINE__); 
	
	std::vector<const Field*> fields(strfields.size());	
	unsigned int i = 0;
	const Field* field;
	for(const char* strfield : strfields)
	{
		field = table->find(strfield);
		if(not field) throw Exception(Exception::NO_FOUND_FIELD,strfield,__FILE__,__LINE__);
		
		fields[i] = field;
		
		i++;
	}
}

}

