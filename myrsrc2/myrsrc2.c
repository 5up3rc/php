#include "myrsrc2.h"

static int le_myrsrc2_descriptor;
static int le_myrsrc2_descriptor_persist;
static zend_function_entry myrsrc2_functions[] = {
	ZEND_FE(myrsrc2_fopen, NULL)
	ZEND_FE(myrsrc2_fwrite, NULL)
	ZEND_FE(myrsrc2_fclose, NULL)
	ZEND_FE(myrsrc2_fname, NULL)
	{NULL, NULL, NULL}
};
static void myrsrc2_descriptor_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC) {
	myrsrc2_descriptor_data *fdata = (myrsrc2_descriptor_data *)rsrc->ptr;
	fclose(fdata->fp);
	efree(fdata->filename);
	efree(fdata);
}
static void myrsrc2_descriptor_dtor_persistent(zend_rsrc_list_entry *rsrc TSRMLS_DC) {
	myrsrc2_descriptor_data *fdata = (myrsrc2_descriptor_data *)rsrc->ptr;
	fclose(fdata->fp);
	pefree(fdata->filename, 1);
	pefree(fdata, 1);
}
zend_module_entry myrsrc2_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"myrsrc2",
	myrsrc2_functions,
	ZEND_MINIT(myrsrc2),
	NULL,
	NULL,
	NULL,
	NULL,
#if ZEND_MODULE_API_NO >= 20010901
	"0.1",
#endif
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_MYRSRC2
ZEND_GET_MODULE(myrsrc2)
#endif

ZEND_MINIT_FUNCTION(myrsrc2)
{
	le_myrsrc2_descriptor = zend_register_list_destructors_ex(myrsrc2_descriptor_dtor, NULL, MYRSRC2_DESCRIPTOR_NAME, module_number);
	le_myrsrc2_descriptor_persist = zend_register_list_destructors_ex(NULL, myrsrc2_descriptor_dtor_persistent, MYRSRC2_DESCRIPTOR_NAME, module_number);
	return SUCCESS;
}

ZEND_FUNCTION(myrsrc2_fopen)
{
	myrsrc2_descriptor_data *fdata;
	FILE *fp;
	char *filename, *mode, *hash_key;
	int filename_len, mode_len, hash_key_len;
	zend_bool persist = 0;
	zend_rsrc_list_entry *fexist;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss|b", &filename, &filename_len, &mode, &mode_len, &persist) == FAILURE) {
		RETURN_NULL();
	}
	if(!filename_len || !mode_len) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid filename or mode length");
		RETURN_FALSE;
	}
	fp = fopen(filename, mode);
	if(!fp) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid filename or mode length");
		RETURN_FALSE;
	}

	hash_key_len = spprintf(&hash_key, 0, "myrsrc2_descriptor:%s:%s", filename, mode);
	if(zend_hash_find(&EG(persistent_list), hash_key, hash_key_len + 1, (void **)&fexist) == SUCCESS) {
	    ZEND_REGISTER_RESOURCE(return_value, fexist->ptr, le_myrsrc2_descriptor_persist);
	    efree(hash_key);
		php_printf("\n- RSRC Existing -\n");
	    return;
	}
	if(!persist) {
		fdata = emalloc(sizeof(myrsrc2_descriptor_data));
		fdata->fp = fp;
		fdata->filename = estrndup(filename, filename_len);
		ZEND_REGISTER_RESOURCE(return_value, fdata, le_myrsrc2_descriptor);
	} else {
		zend_rsrc_list_entry le;
		fdata = pemalloc(sizeof(myrsrc2_descriptor_data), 1);
		fdata->filename = pemalloc(filename_len + 1, 1);
		memcpy(fdata->filename, filename, filename_len + 1);
		fdata->fp = fp;

		//在EG(regular_list中存一份)
		ZEND_REGISTER_RESOURCE(return_value, fdata, le_myrsrc2_descriptor_persist);

		//在EG(persistent_list)中再存一份
		le.type = le_myrsrc2_descriptor_persist;
		le.ptr = fdata;
		zend_hash_update(&EG(persistent_list), hash_key, hash_key_len + 1, (void *)&le, sizeof(zend_rsrc_list_entry), NULL);
	}
	efree(hash_key);
}

ZEND_FUNCTION(myrsrc2_fwrite)
{
	myrsrc2_descriptor_data *fdata;
	zval *file_rsrc;
	char *data;
	int data_len;
	zend_bool persist = 0;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rs|b", &file_rsrc, &data, &data_len, &persist) == FAILURE) {
		RETURN_NULL();
	}
	if(persist) {
		ZEND_FETCH_RESOURCE(fdata, myrsrc2_descriptor_data*, &file_rsrc, -1, MYRSRC2_DESCRIPTOR_NAME, le_myrsrc2_descriptor_persist);
	} else {
		ZEND_FETCH_RESOURCE(fdata, myrsrc2_descriptor_data*, &file_rsrc, -1, MYRSRC2_DESCRIPTOR_NAME, le_myrsrc2_descriptor);
	}
	RETURN_LONG(fwrite(data, 1, data_len, fdata->fp));
}

ZEND_FUNCTION(myrsrc2_fclose)
{
	myrsrc2_descriptor_data *fdata;
	zval *file_rsrc;
	zend_bool persist = 0;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r|b", &file_rsrc, &persist) == FAILURE) {
		RETURN_NULL();
	}
	if(persist) {
		ZEND_FETCH_RESOURCE(fdata, myrsrc2_descriptor_data*, &file_rsrc, -1, MYRSRC2_DESCRIPTOR_NAME, le_myrsrc2_descriptor_persist);
		zend_hash_index_del(&EG(persistent_list), Z_RESVAL_P(file_rsrc));
	} else {
		ZEND_FETCH_RESOURCE(fdata, myrsrc2_descriptor_data*, &file_rsrc, -1, MYRSRC2_DESCRIPTOR_NAME, le_myrsrc2_descriptor);
		zend_hash_index_del(&EG(regular_list), Z_RESVAL_P(file_rsrc));
	}
	RETURN_TRUE;
}

ZEND_FUNCTION(myrsrc2_fname)
{
	myrsrc2_descriptor_data *fdata;
	zval *file_rsrc;
	zend_bool persist = 0;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r|b", &file_rsrc, &persist) == FAILURE) {
		RETURN_NULL();
	}
	if(persist) {
		ZEND_FETCH_RESOURCE(fdata, myrsrc2_descriptor_data*, &file_rsrc, -1, MYRSRC2_DESCRIPTOR_NAME, le_myrsrc2_descriptor_persist);
	} else {
		ZEND_FETCH_RESOURCE(fdata, myrsrc2_descriptor_data*, &file_rsrc, -1, MYRSRC2_DESCRIPTOR_NAME, le_myrsrc2_descriptor);
	}
	RETURN_STRING(fdata->filename, 1);
}
