#include "myclass.h"

zend_module_entry myclass_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"myclass",
	NULL,
	ZEND_MINIT(myclass),
	NULL,
	NULL,
	NULL,
	NULL,
#if ZEND_MODULE_API_NO >= 20010901
	"0.1",
#endif
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_MYCLASS
ZEND_GET_MODULE(myclass)
#endif

zend_class_entry *ce_myclass; //以备引用

ZEND_METHOD(myclass, __construct)
{
	php_printf("__construct\n");
}
ZEND_METHOD(myclass, method1)
{
	php_printf("method1\n");
}
static zend_function_entry myclass_methods[] = {
	ZEND_ME(myclass, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR) //构造方法
	ZEND_ME(myclass, method1, NULL, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};

ZEND_MINIT_FUNCTION(myclass)
{
	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce, "myclass", myclass_methods);
	ce_myclass = zend_register_internal_class(&ce TSRMLS_CC);

	zend_declare_property_null(ce_myclass, "prop1", strlen("prop1"), ZEND_ACC_PUBLIC TSRMLS_CC); //定义public属性prop1
	return SUCCESS;
}

