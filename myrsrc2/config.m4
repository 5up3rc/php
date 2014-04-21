PHP_ARG_ENABLE(myrsrc2,
    [Wether to enable "myrsrc2" extension],
    [--enable-myrsrc2	Enable "myrsrc2" extension support]
)

if test $PHP_MYRSRC2 != "no"; then
    PHP_SUBST(MYRSRC2_SHARED_LIBADD)
    PHP_NEW_EXTENSION(myrsrc2, myrsrc2.c, $ext_shared)
fi
