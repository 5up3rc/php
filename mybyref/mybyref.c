#include "mybyref.h"

/**
 * 运行时传引用(Call-time Pass-by-ref)
 * <?php
 *	function mybyref_calltime($a) {
 *		 $a = "modified-by-ref";
 *	}
 *	$a = 'a-string';
 *	mybyref_calltime(&$a); //@see allow_call_time_pass_reference
 */
ZEND_FUNCTION(mybyref_calltime)
{
	zval *a;
	
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &a) == FAILURE) {
		RETURN_NULL();
	}
	
	if(!a->is_ref__gc) { //不是以引用的方式传递的
		return;
	}
	
	convert_to_string(a);
	
	ZVAL_STRING(a, "modified-by-ref", 1);
	return;	
}

/**
 * 编译时传引用(Compile-time Pass-by-ref)
 * <?php
 *	function mybyref_compiletime(&$a) {
 *		 $a = "modified-by-ref";
 *	}
 *	$a = 'a-string';
 *	mybyref_compiletime($a);
 */
ZEND_FUNCTION(mybyref_compiletime)
{
	zval *a;
	
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &a) == FAILURE) {
		RETURN_NULL();
	}
	
	if(!a->is_ref__gc) { //不是以引用的方式传递的
		return;
	}
	
	convert_to_string(a);
	
	ZVAL_STRING(a, "modified-by-ref", 1);
	return;	
}

#ifdef ZEND_ENGINE_2
	ZEND_BEGIN_ARG_INFO(mybyref_compiletime_arginfo, 0)
		ZEND_ARG_PASS_INFO(1)
	ZEND_END_ARG_INFO()
#else /* ZEND ENGINE 1 */
static unsigned char mybyref_compiletime_arginfo[] = {1, BYREF_FORCE};
#endif

static zend_function_entry mybyref_functions[] = {
	ZEND_FE(mybyref_calltime, NULL)
	ZEND_FE(mybyref_compiletime, mybyref_compiletime_arginfo)
	//ZEND_FALIAS(mybyref_compiletime, mybyref_calltime, mybyref_compiletime_arginfo)
	{NULL, NULL, NULL}
};

zend_module_entry mybyref_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"mybyref",
	mybyref_functions, //Functions
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

#ifdef COMPILE_DL_MYBYREF
ZEND_GET_MODULE(mybyref)
#endif
