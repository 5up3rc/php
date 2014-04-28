PHP_ARG_ENABLE(myglobals,
	[Wether to enable the "myglobals" extension],
	[--enable-myglobals	Enable "myglobals" extension support])

if test $PHP_MYGLOBALS != "no"; then
	PHP_SUBST(MYGLOBALS_SHARED_LIBADD)
	PHP_NEW_EXTENSION(myglobals, myglobals.c, $ext_shared)
fi

