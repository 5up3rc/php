#include "myglobals.h"

static zend_function_entry myglobals_functions[] = {
	    ZEND_FE(myglobals_counter, NULL)
	    {NULL, NULL, NULL}
};

zend_module_entry myglobals_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"myglobals",
	myglobals_functions,
	ZEND_MINIT(myglobals),
	ZEND_MSHUTDOWN(myglobals),
	NULL,
	NULL,
	NULL,
#if ZEND_MODULE_API_NO >= 20010901
	"0.1",
#endif
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_MYGLOBALS
ZEND_GET_MODULE(myglobals)
#endif

ZEND_DECLARE_MODULE_GLOBALS(myglobals); //声明定义好的全局变量

int myglobals_globals_id;
static void myglobals_globals_ctor(zend_myglobals_globals *myglobals_globals TSRMLS_DC) {
	myglobals_globals->counter = 0;
}

static void myglobals_globals_dtor(zend_myglobals_globals *myglobals_globals TSRMLS_DC) {

}

ZEND_MINIT_FUNCTION(myglobals)
{
#ifdef ZTS
	ts_allocate_id(&myglobals_globals_id,
			sizeof(zend_myglobals_globals),
			(ts_allocate_ctor)myglobals_globals_ctor,
			(ts_allocate_dtor)myglobals_globals_dtor);
#else
	myglobals_globals_ctor(&myglobals_globals TSRMLS_CC);
#endif
	return SUCCESS;
}

ZEND_MSHUTDOWN_FUNCTION(myglobals)
{
#ifndef ZTS
	myglobals_globals_dtor(&myglobals_globals TSRMLS_CC);
#endif
	return SUCCESS;
}

ZEND_FUNCTION(myglobals_counter)
{
#ifdef ZTS
	php_printf("By ZTS\n");
	RETURN_LONG(++TSRMG(myglobals_globals_id, zend_myglobals_globals *, counter));
#else
	RETURN_LONG(++myglobals_globals.counter);
#endif
}

