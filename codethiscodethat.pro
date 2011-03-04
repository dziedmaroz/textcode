#-------------------------------------------------
#
# Project created by QtCreator 2011-02-18T14:59:56
#
#-------------------------------------------------

QT       -= core

QT       -= gui

TARGET = codethiscodethat
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    crypt.cpp \
    code.cpp

HEADERS += \
    main.h \
    crypt.h \
    code.h \
    structdef.h

OTHER_FILES += \
    codethis.conf \
    open.txt \
    ../codethiscodethat-build-desktop/crypted.txt
