#ifndef MYINTERFACE_H
#define MYINTERFACE_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"

extern zend_module_entry myinterface_module_entry;

ZEND_MINIT_FUNCTION(myinterface);

#endif /* MYINTERFACE_H */

