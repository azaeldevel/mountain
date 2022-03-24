
#include <fstream>
#include <iostream>

#include "Generator.hh"
#include "Exception.hh"

namespace oct::mont
{


struct table_fields
{
	const Table* table;
	std::list<const Field*> fields;
};
void Generator::engines(std::ofstream& result)const
{

	result << "#ifndef " << database->get_name() << "_ENGINES_HH" "\n";
	result << "#define " << database->get_name() << "_ENGINES_HH" "\n";
	
	result << "typedef Index unsigned int;\n";
		
	/*std::list<table_fields> tables;
	unsigned int count_pk;
	unsigned int count_index;
	for(const Table& table : database->get_tables())
	{
		//std::cout << "Table : " << table.get_name() << "\n";
		tables.push_back(table_fields());
		tables.back().table = &table;
		count_pk = 0;
		count_index = 0;
		for(const Field& field : table.get_fields())
		{
			if(field.is_fixed())
			{
				//std::cout << "\tField fixed : " << field.get_name();
				tables.back().fields.push_back(&field);
			}
			else
			{
				throw Exception(Exception::FAIL_GENERATION_ENGINE_NOT_DINAMIC_LENGTH,__FILE__,__LINE__);
			}
			if(field.is_pk()) count_pk++;
			if(field.is_index()) count_index++;
		}	
		if(count_pk > 1) throw Exception(Exception::FAIL_GENERATION_ENGINE_MULTKEY,__FILE__,__LINE__);
		if(count_index > 1) throw Exception(Exception::FAIL_GENERATION_ENGINE_MULTKEY,__FILE__,__LINE__);
	}*/
	for(const Table& table : database->get_tables())
	{
		result << "\n";
		indexs(table,result);
	}
	/*for(const table_fields& table : database->get_tables())
	{
		result << "\n";
		container(*table.table,NULL,table.fields,result);
	}*/
	
	result << "\n";
	
	const Field* pk_field = NULL;
	for(const Table& table : database->get_tables())
	{
		result << "class "  << table.get_name() << " : public oct::sat::Engine<" << table.get_singular() << ",Index,Index>\n";
		result << "{\n";
		
		result << "};\n";
	}
	
	result << "\n";	
	
	result << "\n#endif";
}
void Generator::engines(const Table& table,std::ofstream& result)const
{

}


}