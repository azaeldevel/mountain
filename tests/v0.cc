
#include <CUnit/Basic.h>
#include <iostream>

#include "../src/Database.hh"

static std::string bdir;

int init(void)
{
	return 0;
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean(void)
{
	return 0;
}

void testDeveloping()
{
	oct::mont::Database db("../../tests/DB");
	
	CU_ASSERT(strcmp(db.get_name(),"testdb") == 0);
	CU_ASSERT(db.get_tables().size() == 3);
	/*for(const oct::mont::Table& table : db.get_tables())
	{
		std::cout << "\tTable : " << table.get_name() << ", " << table.get_length() << std::endl;
	}*/
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
