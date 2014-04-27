#ifndef MYCONST_H
#define MYCONST_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"
#define MYCONST_EXT_VER "0.1"

ZEND_MINIT_FUNCTION(myconst);
extern zend_module_entry myconst_module_entry;

#endif /* MYCONST_H */

