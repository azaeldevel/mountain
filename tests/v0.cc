
#include <CUnit/Basic.h>
#include <iostream>

#include "../src/Database.hh"
#include "../src/Generator.hh"


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
	const std::string result_patter = "struct testPersons{unsigned int id;char name;char ap;};";
	std::string strcontainer;
	Generator gen(db);
	gen.build("Persons",fields,"testPersons",strcontainer,false);
	//std::cout << strcontainer << "\n";
	if(result_patter.compare(strcontainer) == 0)CU_ASSERT(true)
	else CU_ASSERT(false);
}


int main(int argc, char *argv[])
{  

	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();
	CU_pSuite pSuite = NULL;
	pSuite = CU_add_suite("Testing Mountain DB", init, clean);
	if (NULL == pSuite)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if ((NULL == CU_add_test(pSuite, "Developing", testDeveloping)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
			

	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();	
}
