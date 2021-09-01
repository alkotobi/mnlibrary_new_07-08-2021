TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        mnsql_table.c\
        mndatabase_test.c \
        sqlite3.c\
        mndatabase.c \
        mnrecordset.c \
        mnsql.c\
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
        mnrecord.c \
        mnrecord_test.c \
        mnstring.c \
        mntypes.c \
        test.c \
        tvariant_test.c

HEADERS += \
    mnsql_table.h\
    mndatabase_test.h \
    sqlite3.h\
    mndatabase.h \
    mnrecordset.h \
    mnsql.h\
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
    mnrecord.h \
    mnrecord_test.h \
    mnstring.h \
    mntypes.h \
    test.h \
    tvariant_test.h
