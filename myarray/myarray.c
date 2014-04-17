#include "myarray.h"

ZEND_FUNCTION(myarray_show)
{
	zval *subarr;
	
	array_init(return_value); //创建数组
	
	add_assoc_long(return_value, "age", 25); //字符串键=>值
	add_index_bool(return_value, 123, 1); //下标=>值
	add_next_index_double(return_value, 3.1415926535); //自动下标 [] = 值
	add_next_index_string(return_value, "dup1", 1);
	
	MAKE_STD_ZVAL(subarr);
	array_init(subarr);
	
	add_next_index_long(subarr, 1);
	add_next_index_long(subarr, 8);
	add_next_index_long(subarr, 10);
	
	add_index_zval(return_value, 444, subarr);
}

static zend_function_entry myarray_functions[] = {
	ZEND_FE(myarray_show, NULL)
	{NULL, NULL, NULL}
};

zend_module_entry myarray_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"myarray",
	myarray_functions, //FUNCTIONS
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

#ifdef COMPILE_DL_MYARRAY
ZEND_GET_MODULE(myarray)
#endif
