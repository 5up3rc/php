#include "myminfo.h"

zend_module_entry myminfo_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"myminfo",
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	ZEND_MINFO(myminfo),
#if ZEND_MODULE_API_NO >= 20010901
	MYMINFO_EXT_VER,
#endif
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_MYMINFO
ZEND_GET_MODULE(myminfo)
#endif

ZEND_MINFO_FUNCTION(myminfo)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "Myminfo Module", "enabled");
	php_info_print_table_row(2, "Version", MYMINFO_EXT_VER);
	if(sapi_module.phpinfo_as_text) { //纯文本
		php_info_print_table_row(2, "By", "TShiChun Test\n2014.04");
	} else { //HTML
		php_printf("<tr>"
			"<td>By</td>"
			"<td><a href=\"http://phpman.org\">TShiChun</a> Test<br/>2014.04</td>"
			"</tr>");
	}
	php_info_print_table_end();
}

