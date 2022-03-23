
#include "Generator.hh"
#include "Exception.hh"

namespace oct::mont
{



Generator::Generator(const Database& db) : database(&db)
{
}

bool Generator::build(const char* table,const std::vector<const char*>& strfileds,const char* name,std::string& result,bool human_readable)
{
	std::vector<const Field*> fields;
	
	if(not maping_fields(table,strfileds,fields)) throw Exception(Exception::FAIL_BUILD_GENERATION,__FILE__,__LINE__,table);
	
	result = "struct ";
	result += name;
	if(human_readable) result += "\n";
	result += "{";
	for(unsigned int i = 0; i < fields.size(); i++)
	{
		if(not fields[i]) throw Exception(Exception::FAIL_BUILD_GENERATION,__FILE__,__LINE__,table);
		
		if(human_readable) result += "\n";
		result += fields[i]->get_type_cstr();
		result += " ";
		result += fields[i]->get_name();
		if(fields[i]->get_length() != Field::type_size(fields[i]->get_type()))
		{
			unsigned int length;
			length = fields[i]->get_length() / Field::type_size(fields[i]->get_type());
			result += "[";
			result += std::to_string(length);
			result += "]";
		}
		result += ";";		
	}
	if(human_readable) result += "\n";
	result += "};";
	
	return true; 
}

bool Generator::maping_fields(const char* strtable,const std::vector<const char*>& strfields,std::vector<const Field*>& result)
{
	const Table* table = database->find(strtable);
	if(not table) throw Exception(Exception::NO_FOUND_TABLE,__FILE__,__LINE__,strtable); 
	
	//std::vector<const Field*> fields(strfields.size());	
	unsigned int i = 0;
	const Field* field;
	if(result.size() != strfields.size()) result.resize(strfields.size());
	for(const char* strfield : strfields)
	{
		field = table->find(strfield);
		if(not field) throw Exception(Exception::NO_FOUND_FIELD,__FILE__,__LINE__,strfield);
		
		result[i] = field;
		
		i++;
	}
	if(i != result.size()) throw Exception(Exception::FAIL_ON_MAPPING_FIEL,__FILE__,__LINE__);
	
	return true;
}

}

