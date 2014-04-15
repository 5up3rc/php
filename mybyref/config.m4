PHP_ARG_ENABLE(mybyref,
	[Wether to enable "mybyref" extension],
	[  --enable-mybyref    Enable "mybyref" extension support]
)

if test $PHP_MYBYREF != "no"; then
	PHP_SUBST(MYBYREF_SHARED_LIBADD)
	PHP_NEW_EXTENSION(mybyref, mybyref.c, $ext_shared)
fi
