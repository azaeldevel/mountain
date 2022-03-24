#include <fstream>


#include "Generator.hh"
#include "Exception.hh"

namespace oct::mont
{


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
void Generator::container(const Field& field,const char* name,std::ofstream& result)const
{
	if(human_readable) result << "\n";
	if(name) result << name;
	else result << field.get_type_cstr();
	result << " ";
	result << field.get_name();
	if(field.get_length() != field.type_size())
	{
		unsigned int length;
		length = field.get_length() / field.type_size();
		result << "[";
		result << std::to_string(length);
		result << "]";
	}
	result << ";";
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
void Generator::container(const Table& table,const char* name, std::ofstream& result)const
{
	result << "struct ";
	if(name) result << name;
	else result << table.get_singular();
	if(human_readable) result << "\n";
	result << "{";
	for(const Field& field : table.get_fields())
	{
		container(field,NULL,result);
	}
	if(human_readable) result << "\n";
	result << "};";
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
void Generator::container(const Table& table,const char* name,std::list<const Field*> fields,std::ofstream& result)const
{
	result << "struct ";
	if(name) result << name;
	else result << table.get_singular();
	if(human_readable) result << "\n";
	result << "{";
	for(const Field* field : fields)
	{
		container(*field,NULL,result);
	}
	if(human_readable) result << "\n";
	result << "};";
}
void Generator::container(std::string& result)const
{
	for(const Table& table : database->get_tables())
	{
		result += "\nx";
		container(table,NULL,result);
	}
}





void Generator::container(std::ofstream& result)const
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
	const Table* table = database->find(strtable);
	if(not table) throw Exception(Exception::NO_FOUND_TABLE,strtable,__FILE__,__LINE__);
	
	std::list<const Field*> fields;	
	if(not maping_fields(strtable,strfields,fields)) throw Exception(Exception::FAIL_BUILD_GENERATION,strtable,__FILE__,__LINE__);
	
	container(*table,name,fields,result);
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


}