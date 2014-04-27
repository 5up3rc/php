#ifndef MYMINFO_H
#define MYMINFO_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"
#include "SAPI.h"
#define MYMINFO_EXT_VER "0.1"

ZEND_MINFO_FUNCTION(myminfo);
extern zend_module_entry myminfo_module_entry;

#endif /* MYMINFO_H */
