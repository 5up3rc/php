PHP_ARG_ENABLE(myparam,
	[Wether to enable "myparam" extension],
	[--enable-myparam	Enable "myparam" extension support]
)

if test $PHP_MYPARAM != "no"; then
	PHP_SUBST(MYPARAM_SHARED_LIBADD)
	PHP_NEW_EXTENSION(myparam, myparam.c, $ext_shared)
fi
