PHP_ARG_ENABLE(myrsrc,
	[Wether to enable "myrsrc" extension],
	[--enable-myrsrc	Enable "myrsrc" extension support]
)

if test $PHP_MYRSRC != "no"; then
	PHP_SUBST(MYRSRC_SHARED_LIBADD)
	PHP_NEW_EXTENSION(myrsrc, myrsrc.c, $ext_shared)
fi
