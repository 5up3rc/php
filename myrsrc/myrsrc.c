#include "myrsrc.h"

#define MYRSRC_DESCRIPTOR_RES_NAME "My Rsrc Descriptor"
static int myrsrc_descriptor;
static void myrsrc_descriptor_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC) //unset($res)
{
	FILE *fp = (FILE *)rsrc->ptr;
	fclose(fp);
}
ZEND_MINIT_FUNCTION(myrsrc)
{
	myrsrc_descriptor = zend_register_list_destructors_ex(
			myrsrc_descriptor_dtor,
			NULL,
			MYRSRC_DESCRIPTOR_RES_NAME,
			module_number);
	php_printf("MINIT\n");
	return SUCCESS;
}
ZEND_FUNCTION(myrsrc_fopen)
{
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
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Unable to open %s using mode %s", filename, mode);
		RETURN_FALSE;
	}
	ZEND_REGISTER_RESOURCE(return_value, fp, myrsrc_descriptor); //The "fp" adding resource pool
}
ZEND_FUNCTION(myrsrc_fwrite)
{
	FILE *fp;
	zval *file_rsrc;
	char *data;
	int data_len;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rs", &file_rsrc, &data, &data_len) == FAILURE) {
		RETURN_NULL();
	}
	ZEND_FETCH_RESOURCE(fp, FILE*, &file_rsrc, -1, MYRSRC_DESCRIPTOR_RES_NAME, myrsrc_descriptor);
	RETURN_LONG(fwrite(data, 1, data_len, fp));
}
ZEND_FUNCTION(myrsrc_fclose)
{
	FILE *fp;
	zval *file_rsrc;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &file_rsrc) == FAILURE) {
		RETURN_NULL();
	}
	ZEND_FETCH_RESOURCE(fp, FILE*, &file_rsrc, -1, MYRSRC_DESCRIPTOR_RES_NAME, myrsrc_descriptor);

	zend_hash_index_del(&EG(regular_list), Z_RESVAL_P(file_rsrc)); //unset($res)
	RETURN_TRUE;
}
static zend_function_entry myrsrc_functions[] = {
	ZEND_FE(myrsrc_fopen, NULL)
	ZEND_FE(myrsrc_fwrite, NULL)
	ZEND_FE(myrsrc_fclose, NULL)
	{NULL, NULL, NULL}
};
zend_module_entry myrsrc_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"myrsrc",
	myrsrc_functions,
	ZEND_MINIT(myrsrc),
	NULL,
	NULL,
	NULL,
	NULL,
#if ZEND_MODULE_API_NO >= 20010901
	"0.1",
#endif
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_MYRSRC
ZEND_GET_MODULE(myrsrc)
#endif
