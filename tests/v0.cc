


#include "v0.hh"

using namespace oct::mont;

int init(void)
{
	if(not std::filesystem::exists("../../tests"))
	{
		std::cout << "No esta en el directorio correcto\n";
		return 1;
	}
	
	return 0;
}

int clean(void)
{
	return 0;
}

void testDeveloping()
{
	oct::mont::Database db("../../tests/DB");
	
	CU_ASSERT(strcmp(db.get_name(),"testdb") == 0);
	CU_ASSERT(db.get_tables().size() == 3);
	std::vector<const char*> fields;
	unsigned int i_fields = 0;
	for(const oct::mont::Table& table : db.get_tables())
	{
		//std::cout << "\tTable - (TEST): " << table.get_name() << std::endl;
		if(strcmp(table.get_name(),"Persons") == 0)
		{
			//std::cout << "\t\tname : " << table.get_name() << std::endl;
			if(table.get_fields().size() == 3)
			{
				CU_ASSERT(true);
			}
			else
			{
				std::cout << "\t\ttable.get_fields().size() es " << table.get_fields().size() << std::endl;
				CU_ASSERT(false);
			}
			fields.resize(table.get_fields().size());
			for(const oct::mont::Field& field : table.get_fields())
			{
				//std::cout << "\t\t" << field.get_name() << "," << field.get_type() << std::endl;
				
				if(strcmp(field.get_name(),"id") == 0)
				{
					CU_ASSERT(field.get_type() == oct::mont::Field::Type::UNSIGNED_INT);
					CU_ASSERT(field.get_pk());
					CU_ASSERT(field.get_length() == sizeof(unsigned int));
					CU_ASSERT(field.get_auto_inc());
					fields[i_fields] = field.get_name();
				}
				if(strcmp(field.get_name(),"name") == 0)
				{
					CU_ASSERT(field.get_type() == oct::mont::Field::Type::CHAR);
					CU_ASSERT(field.get_pk() == false);
					CU_ASSERT(field.get_length() == 30);
					fields[i_fields] = field.get_name();
				}	
				if(strcmp(field.get_name(),"ap") == 0)
				{
					CU_ASSERT(field.get_type() == oct::mont::Field::Type::CHAR);
					CU_ASSERT(field.get_pk() == false);
					CU_ASSERT(field.get_length() == 30);
					fields[i_fields] = field.get_name();
				}
				i_fields++;
			}
		}
	}
	
	CU_ASSERT(fields.size() > 0);
	const std::string result_pattern = "struct testPersons{unsigned int id;char name[30];char ap[30];};";
	std::string strcontainer;
	Generator gen(db);
	gen.build("Persons",fields,"testPersons",strcontainer,false);
	//std::cout << strcontainer << "\n";
	if(result_pattern.compare(strcontainer) == 0) CU_ASSERT(true)
	else CU_ASSERT(false);
	
	const std::string result_pattern2 = "struct testPersons{unsigned int id;char name[30];};";
	std::vector<const char*> fields_person2(fields);
	fields_person2.pop_back();
	std::string strcontainer2;
	gen.build("Persons",fields_person2,"testPersons",strcontainer2,false);
	//std::cout << strcontainer2 << "\n";
	if(result_pattern2.compare(strcontainer2) == 0) CU_ASSERT(true)
	else CU_ASSERT(false);
	
	std::vector<const char*> fields_person3(fields);
	std::string strcontainer3;
	fields_person3[fields_person2.size()/2] = "failfield";
	try
	{
		gen.build("Persons",fields_person3,"testPersons",strcontainer3,false);
	}
	catch(const Exception& ex)
	{
		CU_ASSERT( ex.code() == Exception::NO_FOUND_FIELD);
	}
}

