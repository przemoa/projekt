#-------------------------------------------------
#
# Project created by QtCreator 2014-07-01T17:05:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = serwerv1
TEMPLATE = app


SOURCES += main.cpp\
        glowneokno.cpp \
    cSerwer.cpp \
    gra/cBelka.cpp \
    gra/cBohater.cpp \
    gra/cBohater1.cpp \
    gra/cBohater2.cpp \
    gra/cElement.cpp \
    gra/cGracz.cpp \
    gra/cJednostka.cpp \
    gra/cPlansza.cpp \
    gra/cPunktStabilny.cpp \
    gra/cStworek.cpp \
    gra/cTeownik.cpp \
    gra/cZamek.cpp \
    gra/cObiekt.cpp

HEADERS  += glowneokno.h \
    cSerwer.h \
    gra/cBelka.h \
    gra/cBohater.h \
    gra/cBohater1.h \
    gra/cBohater2.h \
    gra/cElement.h \
    gra/cGracz.h \
    gra/cJednostka.h \
    gra/cPlansza.h \
    gra/cPunktStabilny.h \
    gra/cStworek.h \
    gra/cTeownik.h \
    gra/cZamek.h \
    gra/naglowki.h \
    gra/cObiekt.h

FORMS    += glowneokno.ui



LIBS += -lws2_32
