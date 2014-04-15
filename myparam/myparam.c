#include "myparam.h"

ZEND_FUNCTION(myparam_hello) //单个参数
{
	char *name;
	int name_len;
	
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &name, &name_len) == FAILURE) {
		RETURN_NULL();
	}
	php_printf("Hello ");
	PHPWRITE(name, name_len);
	php_printf("!\n");
}

ZEND_FUNCTION(myparam_hello_more) //多个参数
{
	char *name;
	int name_len;
	char *greet;
	int greet_len;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &name, &name_len, &greet, &greet_len) == FAILURE) {
		RETURN_NULL();
	}
	php_printf("Hello ");
	PHPWRITE(greet, greet_len);
	php_printf(" ");
	PHPWRITE(name, name_len);
	php_printf("!\n");
}

ZEND_FUNCTION(myparam_var_dump) //可变参数
{
	int i, argc = ZEND_NUM_ARGS();
	zval ***args;
	
	args = (zval ***)safe_emalloc(argc, sizeof(zval **), 0);
	if(ZEND_NUM_ARGS() == 0 || zend_get_parameters_array_ex(argc, args) == FAILURE) {
		efree(args);
		WRONG_PARAM_COUNT;
	}
	for(i=0; i<argc; i++) {
		php_var_dump(args[i], 1 TSRMLS_CC);
	}
	efree(args);	
}

ZEND_FUNCTION(myparam_default) //参数默认值
{
	char *name;
	int name_len;
	char *greet = "Mr/Ms";
	int greet_len = sizeof("Mr/Ms") - 1;
	//格式串中的“|”表示其前面的参数为必传的，其后面的参数为选传的，即有默认值，不传则不对参数做处理
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &name, &name_len, &greet, &greet_len) == FAILURE) {
		RETURN_NULL();
	}
	php_printf("Hello ");
	PHPWRITE(greet, greet_len);
	php_printf(" ");
	PHPWRITE(name, name_len);
	php_printf("!\n");
}

ZEND_FUNCTION(myparam_null) //参数传null
{
	zval *val;
	//格式串中的“!”表示当传null变量时，直接把其转成C语言的null，而非封装成IS_NULL类型的zval，以减小开销
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z!", &val) == FAILURE) {
		RETURN_NULL();
	}
	if(!val) {
		val = php_sample_make_defaultval(TSRMLS_C);
	}	
}

static zend_function_entry myparam_functions[] = {
	ZEND_FE(myparam_hello, NULL)
	ZEND_FE(myparam_hello_more, NULL)
	ZEND_FE(myparam_var_dump, NULL)
	ZEND_FE(myparam_default, NULL)
	{NULL, NULL, NULL}
};

zend_module_entry myparam_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"myparam",
	myparam_functions, //FUNCTIONS
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

#ifdef COMPILE_DL_MYPARAM
ZEND_GET_MODULE(myparam)
#endif
