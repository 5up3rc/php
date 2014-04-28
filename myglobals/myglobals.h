//全局变量
#ifndef MYGLOBALS_H
#define MYGLOBALS_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"

ZEND_MINIT_FUNCTION(myglobals);
ZEND_MSHUTDOWN_FUNCTION(myglobals);
ZEND_FUNCTION(myglobals_counter);
extern zend_module_entry myglobals_moudle_entry;
ZEND_BEGIN_MODULE_GLOBALS(myglobals) //定义全局变量
	unsigned long counter;
	//another var.
	//...
ZEND_END_MODULE_GLOBALS(myglobals)

#endif /* MYGLOBALS_H */

