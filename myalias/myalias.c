#include "myalias.h"

ZEND_FUNCTION(myalias_hello)
{
	php_printf("Hello World!\n");
}

static zend_function_entry myalias_functions[] = {
	ZEND_FE(myalias_hello, NULL)
	ZEND_NAMED_FE(myalias_hi, ZEND_FN(myalias_hello), NULL)
	{NULL, NULL, NULL}
};

zend_module_entry myalias_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"myalias",
	myalias_functions, //Functions
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

#ifdef COMPILE_DL_MYALIAS
ZEND_GET_MODULE(myalias)
#endif
