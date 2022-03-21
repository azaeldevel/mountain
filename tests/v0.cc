
#include <CUnit/Basic.h>


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
	
	if ((NULL == CU_add_test(pSuite, "Criterios de comparación semver v1.0.0", testDeveloping)))
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
