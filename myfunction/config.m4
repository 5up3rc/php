PHP_ARG_ENABLE(myfunction,
	[Wether to enable "myfunction" extension],
	[enable-myfunction	Enable "myfunction" extension support]
)

if test $PHP_MYFUNCTION != "no"; then
	PHP_SUBST(MYFUNCTION_SHARED_LIBADD)
	PHP_NEW_EXTENSION(myfunction, myfunction.c, $ext_shared)
fi
