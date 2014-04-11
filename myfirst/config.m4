PHP_ARG_ENABLE(myfirst,
	[Wether to enable the "myfirst" extension],
	[enable-myfirst	Enable "myfirst" extension support])

if test $PHP_MYFIRST != "no"; then
	PHP_SUBST(MYFIRST_SHARED_LIBADD)
	PHP_NEW_EXTENSION(myfirst, myfirst.c, $ext_shared)
fi
