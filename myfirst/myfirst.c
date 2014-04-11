#include "myfirst.h"

zend_module_entry myfirst_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"myfirst", //扩展的名字
	NULL, //Functions
	NULL, //MINIT
	NULL, //MSHUTDOWN
	NULL, //RINIT
	NULL, //RSHUTDOWN
	NULL, //MINFO
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", //扩展的版本号
#endif
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_MYFIRST
ZEND_GET_MODULE(myfirst)
#endif
