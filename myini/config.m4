PHP_ARG_ENABLE(myini,
    [myini],
    [--enable-myini Enable myini]
)

if test $PHP_MYINI != "no"; then
    PHP_SUBST(MYINI_SHARED_LIBADD)
    PHP_NEW_EXTENSION(myini, myini.c, $ext_shared)
fi

