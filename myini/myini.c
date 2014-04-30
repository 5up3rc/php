#include "myini.h"

static zend_function_entry myini_functions[] = {
    ZEND_FE(myini_say, NULL)
    {NULL, NULL, NULL}
};
zend_module_entry myini_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    "myini",
    myini_functions,
    ZEND_MINIT(myini),
    ZEND_MSHUTDOWN(myini),
    NULL,
    NULL,
    NULL,
#if ZEND_MODULE_API_NO >= 20010901
    "0.1",
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_MYINI
ZEND_GET_MODULE(myini)
#endif

ZEND_MINIT_FUNCTION(myini)
{
    REGISTER_INI_ENTRIES();
    return SUCCESS;
}

ZEND_MSHUTDOWN_FUNCTION(myini)
{
    UNREGISTER_INI_ENTRIES();
    return SUCCESS;
}

ZEND_FUNCTION(myini_say)
{
    const char *sayhi = INI_STR("myini.sayhi"); //读取一个字符串配置，char*只属于ZEND引擎，不能修改
    php_printf("%s\n", sayhi);
}

ZEND_INI_MH(myini_sayhi_on_modify) //当配置被修改时
{
    if(new_value_length == 0) { //不允许设置空值
	php_printf("failure\n");
	return FAILURE;
    }
    return SUCCESS;
}

