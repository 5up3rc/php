#include "myinterface.h"

zend_module_entry myinterface_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"myinterface",
	NULL,
	ZEND_MINIT(myinterface),
	NULL,
	NULL,
	NULL,
	NULL,
#if ZEND_MODULE_API_NO >= 20010901
	"0.1",
#endif
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_MYINTERFACE
ZEND_GET_MODULE(myinterface)
#endif

zend_class_entry *ce_myinterface; //以备引用
static zend_function_entry myinterface_methods[] = {
	ZEND_ABSTRACT_ME(myinterface, method1, NULL)
	{NULL, NULL, NULL}
};

ZEND_MINIT_FUNCTION(myinterface)
{
	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce, "myinterface", myinterface_methods);
	ce_myinterface = zend_register_internal_interface(&ce TSRMLS_CC);
	return SUCCESS;
}

