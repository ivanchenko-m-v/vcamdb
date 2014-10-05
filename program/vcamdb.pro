# ============================================================================
#           Project title       :	mac_vcamdb
#           Project description :	MAC camera info database
#           Project version     :
#           Author              :   M. Ivanchenko
#           Date create         :   05-10-2014
#           Date update         :   05-10-2014
#           Comment             :
# ============================================================================
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mac_vcamdb
DESTDIR = ./bin

TEMPLATE = app


SOURCES += \
    app/main.cpp \
    app/application.cpp \
    app/application_params.cpp \
    logic/business_logic.cpp \
    gui/main_window.cpp \
    gui/widget_central.cpp \
    qt_sqlite/qt_sqlite_dbvalue.cpp \
    qt_sqlite/qt_sqlite_connection.cpp \
    qt_sqlite/qt_sqlite_command.cpp \
    qt_sqlite/qt_data_row.cpp \
    qt_sqlite/qt_data_parameter.cpp \

HEADERS  += \
    app/application_params.h \
    app/application.h \
    logic/business_logic.h \
    gui/main_window.h \
    gui/widget_central.h \
    qt_sqlite/qt_sqlite_dbvalue.h \
    qt_sqlite/qt_sqlite_connection.h \
    qt_sqlite/qt_sqlite_command.h \
    qt_sqlite/qt_data_row.h \
    qt_sqlite/qt_data_parameter.h \

INCLUDEPATH += ./app \
				./dbmodule \
				./gui \
				./logic \
				./qt_sqlite

MOC_DIR = ./xmoc

OBJECTS_DIR = ./xobj

RCC_DIR = ./xrcc

RESOURCES += res/app.qrc

TRANSLATIONS += ts/strings_ru.ts

unix: {
LIBS += /usr/lib64/libsqlite3.so
}

#home desktop setiings
#win32: {
#INCLUDEPATH += J:/Qt/sqlite
#LIBS += J:/Qt/sqlite/sqlite3.dll
#RC_FILE = res/winres/app_icon.rc
#}

#home notebook setiings
win32: {
INCLUDEPATH += W:/sqlite3/include
LIBS += W:/sqlite3/sqlite3.dll
RC_FILE = res/winres/app_icon.rc
}
