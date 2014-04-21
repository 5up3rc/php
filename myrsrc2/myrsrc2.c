#include "myrsrc2.h"

static int myrsrc2_descriptor_ld;
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
	myrsrc2_descriptor_ld = zend_register_list_destructors_ex(myrsrc2_descriptor_dtor, NULL, MYRSRC2_DESCRIPTOR_NAME, module_number);
	return SUCCESS;
}

ZEND_FUNCTION(myrsrc2_fopen)
{
	myrsrc2_descriptor_data *fdata;
	FILE *fp;
	char *filename, *mode;
	int filename_len, mode_len;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &filename, &filename_len, &mode, &mode_len) == FAILURE) {
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
	fdata = emalloc(sizeof(myrsrc2_descriptor_data));
	fdata->fp = fp;
	fdata->filename = estrndup(filename, filename_len);
	ZEND_REGISTER_RESOURCE(return_value, fdata, myrsrc2_descriptor_ld);
}

ZEND_FUNCTION(myrsrc2_fwrite)
{
	myrsrc2_descriptor_data *fdata;
	zval *file_rsrc;
	char *data;
	int data_len;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rs", &file_rsrc, &data, &data_len) == FAILURE) {
		RETURN_NULL();
	}
	ZEND_FETCH_RESOURCE(fdata, myrsrc2_descriptor_data*, &file_rsrc, -1, MYRSRC2_DESCRIPTOR_NAME, myrsrc2_descriptor_ld);
	RETURN_LONG(fwrite(data, 1, data_len, fdata->fp));
}

ZEND_FUNCTION(myrsrc2_fclose)
{
	myrsrc2_descriptor_data *fdata;
	zval *file_rsrc;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &file_rsrc) == FAILURE) {
		RETURN_NULL();
	}
	ZEND_FETCH_RESOURCE(fdata, myrsrc2_descriptor_data*, &file_rsrc, -1, MYRSRC2_DESCRIPTOR_NAME, myrsrc2_descriptor_ld);
	zend_hash_index_del(&EG(regular_list), Z_RESVAL_P(file_rsrc));
	RETURN_TRUE;
}

ZEND_FUNCTION(myrsrc2_fname)
{
	myrsrc2_descriptor_data *fdata;
	zval *file_rsrc;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &file_rsrc) == FAILURE) {
		RETURN_NULL();
	}
	ZEND_FETCH_RESOURCE(fdata, myrsrc2_descriptor_data*, &file_rsrc, -1, MYRSRC2_DESCRIPTOR_NAME, myrsrc2_descriptor_ld);
	RETURN_STRING(fdata->filename, 1);
}
