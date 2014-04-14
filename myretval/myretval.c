#include "myretval.h"

ZEND_FUNCTION(myretval_ret)
{
	RETVAL_LONG(101);
	return;
}

static zend_function_entry myretval_functions[] = 
{
	ZEND_FE(myretval_ret, NULL)
	{NULL, NULL, NULL}
};

zend_module_entry myretval_module_entry = 
{
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"myretval",
	myretval_functions, //Functions
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

#ifdef COMPILE_DL_MYRETVAL
ZEND_GET_MODULE(myretval)
#endif
