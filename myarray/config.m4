PHP_ARG_ENABLE(myarray,
	[Wether to enable "myarray" extension],
	[	--enable-myarray	Enable "myarray" extension support]
)

if test $PHP_MYARRAY != "no"; then
	PHP_SUBST(MYARRAY_SHARED_LIBADD)
	PHP_NEW_EXTENSION(myarray, myarray.c, $ext_shared)
fi
