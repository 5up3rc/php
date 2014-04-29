#include "myglobals.h"

zend_module_entry myglobals_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"myglobals",
	NULL,
	NULL,
	NULL,
	ZEND_RINIT(myglobals),
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

zend_bool myglobals_autoglobal_callback(char *name, uint name_len TSRMLS_CC) {
	zval *myglobals_val;
	int i;
	MAKE_STD_ZVAL(myglobals_val);
	array_init(myglobals_val);
	for(i = 0; i < 1000; i++) {
		add_next_index_long(myglobals_val, i);
	}
	ZEND_SET_SYMBOL(&EG(symbol_table), "_MYGLOBALS", myglobals_val);
	return 0;
}

ZEND_RINIT_FUNCTION(myglobals)
{
#ifdef ZEND_ENGINE_2
	myglobals_autoglobal_callback("_MYGLOBALS",
			sizeof("_MYGLOBALS") - 1 TSRMLS_CC);
#endif
	return SUCCESS;
}

