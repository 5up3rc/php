PHP_ARG_ENABLE(myinterface,
	[Wether to enable "myinterface" extension],
	[--enable-myinterface	Enable "myinterface" extension support]
)

if test $PHP_MYINTERFACE != "no"; then
	PHP_SUBST(MYINTERFACE_SHARED_LIBADD)
	PHP_NEW_EXTENSION(myinterface, myinterface.c, $ext_shared)
fi

