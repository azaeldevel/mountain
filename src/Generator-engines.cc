
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
	
	std::list<table_fields> tables;
	for(const Table& table : database->get_tables())
	{
		//std::cout << "Table : " << table.get_name() << "\n";
		tables.push_back(table_fields());
		tables.back().table = &table;
		for(const Field& field : table.get_fields())
		{
			if(field.is_fixed())
			{
				//std::cout << "\tField fixed : " << field.get_name();
				tables.back().fields.push_back(&field);
			}
		}	
	}
	for(const table_fields& table : tables)
	{
		result << "\n";
		container(*table.table,NULL,table.fields,result);
	}
	
	result << "\n#endif";
}
void Generator::engines(const Table& table,std::ofstream& result)const
{

}


}