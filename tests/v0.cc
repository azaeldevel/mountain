


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
	std::list<const char*> fields;
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
			
			for(const oct::mont::Field& field : table.get_fields())
			{
				//std::cout << "\t\t" << field.get_name() << "," << field.get_type() << std::endl;
				
				if(strcmp(field.get_name(),"id") == 0)
				{
					CU_ASSERT(field.get_type() == oct::mont::Field::Type::UNSIGNED_INT);
					CU_ASSERT(field.is_pk());
					CU_ASSERT(field.get_length() == sizeof(unsigned int));
					CU_ASSERT(field.is_auto_inc());
					fields.push_back(field.get_name());
				}
				if(strcmp(field.get_name(),"name") == 0)
				{
					CU_ASSERT(field.get_type() == oct::mont::Field::Type::CHAR);
					CU_ASSERT(field.is_pk() == false);
					CU_ASSERT(field.get_length() == 30);
					fields.push_back(field.get_name());
				}	
				if(strcmp(field.get_name(),"ap") == 0)
				{
					CU_ASSERT(field.get_type() == oct::mont::Field::Type::CHAR);
					CU_ASSERT(field.is_pk() == false);
					CU_ASSERT(field.get_length() == 30);
					fields.push_back(field.get_name());
				}
				i_fields++;
			}
		}
	}
	
	CU_ASSERT(fields.size() > 0);
	const std::string result_pattern = "struct testPersons{unsigned int id;char name[30];char ap[30];};";
	std::string strcontainer;
	Generator gen(db,oct::jup::Jupiter::Lingua::CC);
	gen.container("Persons","testPersons",fields,strcontainer);
	//std::cout << strcontainer << "\n";
	if(result_pattern.compare(strcontainer) == 0) CU_ASSERT(true)
	else CU_ASSERT(false);
	
	const std::string result_pattern2 = "struct testPersons{unsigned int id;char name[30];};";
	std::list<const char*> fields_person2(fields);
	fields_person2.pop_back();
	std::string strcontainer2;
	gen.container("Persons","testPersons",fields_person2,strcontainer2);
	//std::cout << strcontainer2 << "\n";
	if(result_pattern2.compare(strcontainer2) == 0) CU_ASSERT(true)
	else CU_ASSERT(false);
	
	std::list<const char*> fields_person3(fields);
	std::string strcontainer3;
	std::list<const char*>::iterator it3 = fields_person2.begin();
	it3++;
	(*it3)="failfield";
	try
	{
		gen.container("Persons","testPersons",fields_person3,strcontainer3);
	}
	catch(const Exception& ex)
	{
		CU_ASSERT( ex.code() == Exception::NO_FOUND_FIELD);
	}
	
	std::string strcontainer4;
	gen.container(strcontainer4);
	//std::cout << strcontainer4 << "\n";
	
	std::filesystem::path pathcontainer1 = "gen1.hh";
	if(std::filesystem::exists(pathcontainer1)) std::filesystem::remove(pathcontainer1);
	gen.container(pathcontainer1);
	
	std::filesystem::path engines_path1 = "engines1.hh";
	std::ofstream engines_file1;
	engines_file1.open(engines_path1);
	gen.engines(engines_file1);
	engines_file1.flush();
	engines_file1.close();
}

