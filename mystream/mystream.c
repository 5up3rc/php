#include "mystream.h"

ZEND_FUNCTION(mystream_fopen)
{
    php_stream *stream;
    char *path, *mode;
    int path_len, mode_len;
    int options = ENFORCE_SAFE_MODE | REPORT_ERRORS;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &path, &path_len, &mode, &mode_len) == FAILURE){
	return;
    }
    
    stream = php_stream_open_wrapper(path, mode, options, NULL);
    if(!stream) {
	RETURN_FALSE;
    }

    php_stream_to_zval(stream, return_value);
}

ZEND_FUNCTION(mystream_fsockopen)
{
    php_stream *stream;
    char *host, *transport, *errstr = NULL;
    int host_len, transport_len, implicit_tcp = 1, errcode = 0;
    long port = 0;
    int options = ENFORCE_SAFE_MODE;
    int flags = STREAM_XPORT_CLIENT | STREAM_XPORT_CONNECT;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|l", &host, &host_len, &port) == FAILURE) {
	return;
    }

    if(port) {
	int implicit_tcp = 1;
	if(strstr(host, "://")) {
	    implicit_tcp = 0;
	}
	transport_len = spprintf(&transport, 0, "%s%s:%d", implicit_tcp ? "tcp://" : "", host, port);
    } else {
	transport = host;
	transport_len = host_len;
    }

    stream = php_stream_xport_create(transport, transport_len, options, flags, NULL, NULL, NULL, &errstr, &errcode);
    if(transport != host) {
	efree(transport);
    }
    if(errstr) {
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "[%d] %s", errcode, errstr);
	efree(errstr);
    }
    if(!stream) {
	RETURN_FALSE;
    }
    php_stream_to_zval(stream, return_value);
}

ZEND_FUNCTION(mystream_opendir)
{
    php_stream *stream;
    char *path;
    int path_len, options = ENFORCE_SAFE_MODE | REPORT_ERRORS;
    
    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &path, &path_len) == FAILURE) {
	return;
    }

    stream = php_stream_opendir(path, options, NULL);
    if(!stream) {
	RETURN_FALSE;
    }

    php_stream_to_zval(stream, return_value);
}

static zend_function_entry mystream_functions[] = {
    ZEND_FE(mystream_fopen, NULL)
    ZEND_FE(mystream_fsockopen, NULL)
    ZEND_FE(mystream_opendir, NULL)
    {NULL, NULL, NULL}
};

zend_module_entry mystream_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"mystream", 
	mystream_functions, 
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
#if ZEND_MODULE_API_NO >= 20010901
	"0.1",
#endif
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_MYSTREAM
ZEND_GET_MODULE(mystream)
#endif

