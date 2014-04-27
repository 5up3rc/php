//类继承和接口实现
//实例化对象和调用对象方法
//定义和读写对象属性和类静态属性
#ifndef MYCLASS_H
#define MYCLASS_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"

extern zend_module_entry myclass_module_entry;

ZEND_MINIT_FUNCTION(myclass);

#endif /* MYCLASS_H */

