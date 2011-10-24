#-------------------------------------------------
#
# Project created by QtCreator 2011-10-21T10:50:04
#
#-------------------------------------------------

QT       -= core

QT       -= gui

TARGET = MatlabWithTBB
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    tbbtest.cpp

HEADERS += \
    headers.h \
    vstbbmatrix.h \
    mexargcheck.h \
    mexexception.h \
    mexpackage.h \
    mextest.h

INCLUDEPATH += /myfiles/LinuxProject/verbalsaint/include
INCLUDEPATH += /usr/local/MATLAB/R2011a/extern/include

OTHER_FILES += \
    MatlabMexRead.txt



















