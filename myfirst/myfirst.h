#ifndef PHP_MYFIRST_H
#define PHP_MYFIRST_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"
#define phpext_myfirst_ptr &myfirst_module_entry;
extern zend_module_entry myfirst_moudle_entry;

#endif /* PHP_MYFIRST_H */
