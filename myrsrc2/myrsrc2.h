#ifndef MYRSRC2_H
#define MYRSRC2_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"

#define MYRSRC2_DESCRIPTOR_NAME "My Descriptor Name"
ZEND_MINIT_FUNCTION(myrsrc2);
ZEND_FUNCTION(myrsrc2_fopen);
ZEND_FUNCTION(myrsrc2_fwrite);
ZEND_FUNCTION(myrsrc2_fclose);
ZEND_FUNCTION(myrsrc2_fname);
extern zend_module_entry myrsrc2_module_entry;
typedef struct _myrsrc2_descriptor_data {
	char *filename;
	FILE *fp;
} myrsrc2_descriptor_data;

#endif /* MYRSRC2_H  */

