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

zend_class_entry *ce_myclass_parent, *ce_myclass_child, *ce_myinterface; 

ZEND_METHOD(myclass_parent, say)
{
	php_printf("Saying\n");
}
ZEND_METHOD(myclass_child, call_say)
{
	zval *this, *retval, *say;
	MAKE_STD_ZVAL(this);
	MAKE_STD_ZVAL(retval);
	MAKE_STD_ZVAL(say);
	ZVAL_STRINGL(say, "say", sizeof("say") - 1, 1);
	object_init_ex(this, ce_myclass_child); //实例化对象
	call_user_function(NULL, &this, say, retval, 0, NULL TSRMLS_CC); //调用对象方法
	zval_ptr_dtor(&this);
	zval_ptr_dtor(&retval);
	zval_ptr_dtor(&say);
}
static zend_function_entry myinterface_methods[] = {
	ZEND_ABSTRACT_ME(myinterface, say, NULL)
	{NULL, NULL, NULL}
};
static zend_function_entry myclass_parent_methods[] = {
	ZEND_ME(myclass_parent, say, NULL, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};
static zend_function_entry myclass_child_methods[] = {
	ZEND_ME(myclass_child, call_say, NULL, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};

ZEND_MINIT_FUNCTION(myclass)
{
	zend_class_entry ce_c, ce_p, ce_i;
	
	INIT_CLASS_ENTRY(ce_i, "myinterface", myinterface_methods);
	ce_myinterface = zend_register_internal_interface(&ce_i TSRMLS_CC);
	
	INIT_CLASS_ENTRY(ce_p, "myclass_parent", myclass_parent_methods);
	ce_myclass_parent = zend_register_internal_class(&ce_p TSRMLS_CC);
	zend_class_implements(ce_myclass_parent TSRMLS_CC, 1, ce_myinterface); //实现接口

	INIT_CLASS_ENTRY(ce_c, "myclass_child", myclass_child_methods);
	ce_myclass_child = zend_register_internal_class_ex(&ce_c, ce_myclass_parent, "myclass_parent" TSRMLS_CC); //继承父类
	ce_myclass_child->ce_flags |= ZEND_ACC_FINAL_CLASS; //标志为final类，不允许再继承

	return SUCCESS;
}

