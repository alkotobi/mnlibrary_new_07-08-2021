TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        cstring.c\
        cstring_test.c \
        do_test.c \
        main.c \
        mnarray.c \
        mnarray_test.c \
        mnarrayrefs.c \
        mndictionary.c \
        mnfield.c \
        mnfield_test.c \
        mnfunctions.c \
        mnlinked_list.c \
        mnobject.c \
        mnstring.c \
        mntypes.c \
        test.c

HEADERS += \
    cstring.h\
    cstring_test.h \
    do_test.h \
    mnarray.h \
    mnarray_test.h \
    mnarrayrefs.h \
    mndictionary.h \
    mnfield.h \
    mnfield_test.h \
    mnfunctions.h \
    mnlinked_list.h \
    mnobject.h \
    mnstring.h \
    mntypes.h \
    test.h