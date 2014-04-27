PHP_ARG_ENABLE(myconst,
	[Wether to enable "myconst" extension],
	[--enable-myconst	Enable "myconst"]
)

if test $PHP_MYCONST != "no"; then
	PHP_SUBST(MYCONST_SHARED_LIBADD)
	PHP_NEW_EXTENSION(myconst, myconst.c, $ext_shared)
fi

