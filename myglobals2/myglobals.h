//超级全局变量，类似$_GET/$_POST/$_FILES等
#ifndef MYGLOBALS_H
#define MYGLOBALS_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"

ZEND_RINIT_FUNCTION(myglobals);

#endif /* MYGLOBALS_H */

