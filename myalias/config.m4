PHP_ARG_ENABLE(myalias,
	[Wether to enable "myalias" extension],
	[enable-myalias Enable "myalias" extension support]
)

if test $PHP_MYALIAS != "no"; then
	PHP_SUBST(MYALIAS_SHARED_LIBADD),
	PHP_NEW_EXTENSION(myalias, myalias.c, $ext_shared)
fi
