#include "myfunction.h"

ZEND_FUNCTION(myfunction_hello)
{
	php_printf("Hello World!\n");
}

static zend_function_entry myfunction_functions[] = {
	ZEND_FE(myfunction_hello, NULL)
	{NULL, NULL, NULL}
};

zend_module_entry myfunction_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"myfunction",
	myfunction_functions, //Functions
	NULL, //MINIT
	NULL, //MSHUTDOWN
	NULL, //RINIT
	NULL, //RSHUTDOWN
	NULL, //MINFO
#if ZEND_MODULE_API_NO >= 20010901
	"0.1",
#endif
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_MYFUNCTION
ZEND_GET_MODULE(myfunction)
#endif
