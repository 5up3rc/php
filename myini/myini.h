#ifndef MYINI_H
#define MYINI_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"

extern zend_module_entry myini_module_entry;
ZEND_MINIT_FUNCTION(myini);
ZEND_MSHUTDOWN_FUNCTION(myini);
ZEND_FUNCTION(myini_say);
ZEND_INI_MH(myini_sayhi_on_modify);
ZEND_INI_BEGIN()
    ZEND_INI_ENTRY("myini.sayhi", "Hi, Boy!\n\t--by default", ZEND_INI_ALL, myini_sayhi_on_modify)
ZEND_INI_END()
#endif /* MYINI_H */

