PHP_ARG_ENABLE(myretval, 
	[Wether to enable "myretval" extension],
	[--enable-myretval	Enable "myretval" extension support]
)

if test $PHP_MYRETVAL != "no"; then
	PHP_SUBST(MYRETVAL_SHARED_LIBADD)
	PHP_NEW_EXTENSION(myretval, myretval.c, $ext_shared)
fi
