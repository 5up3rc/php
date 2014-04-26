#ifndef MYCLASS_H
#define MYCLASS_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"

extern zend_module_entry myclass_module_entry;

ZEND_MINIT_FUNCTION(myclass);

#endif /* MYCLASS_H */

