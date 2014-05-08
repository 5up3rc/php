PHP_ARG_ENABLE(mystream,
	[Wether to enable the "mystream" extension],
	[--enable-mystream  Enable "mystream" extension support])

if test $PHP_MYSTREAM != "no"; then
	PHP_SUBST(MYSTREAM_SHARED_LIBADD)
	PHP_NEW_EXTENSION(mystream, mystream.c, $ext_shared)
fi

