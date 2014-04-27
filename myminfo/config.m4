PHP_ARG_ENABLE(myminfo,
	[Wether to enable "myminfo" extension],
	[--enable-myminfo	Enable "myminfo"]
)

if test $PHP_MYMINFO != "no"; then
	PHP_SUBST(MYMINFO_SHARED_LIBADD)
	PHP_NEW_EXTENSION(myminfo, myminfo.c, $ext_shared)
fi

