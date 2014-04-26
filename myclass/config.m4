PHP_ARG_ENABLE(myclass,
	[Wether to enable "myclass" extension],
	[--enable-myclass	Enable "myclass" extension support]
)

if test $PHP_MYCLASS != "no"; then
	PHP_SUBST(MYCLASS_SHARED_LIBADD)
	PHP_NEW_EXTENSION(myclass, myclass.c, $ext_shared)
fi

