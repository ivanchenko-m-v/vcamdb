# ============================================================================
#           Project title       :	mac_vcamdb
#           Project description :	MAC camera info database
#           Project version     :
#           Author              :   M. Ivanchenko
#           Date create         :   05-10-2014
#           Date update         :   13-11-2014
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
    app/application_log.cpp \
    qt_sqlite/qt_sqlite_dbvalue.cpp \
    qt_sqlite/qt_sqlite_connection.cpp \
    qt_sqlite/qt_sqlite_command.cpp \
    qt_sqlite/qt_data_row.cpp \
    qt_sqlite/qt_data_parameter.cpp \
    logic/business_logic.cpp \
    gui/main_window.cpp \
    gui/widget_central.cpp \
    gui/widget_cam_selection.cpp \
    gui/widget_tab_object.cpp \
    gui/widget_tab_violation.cpp \
    gui/widget_violation.cpp \
    gui/listview_volation.cpp \
    gui/listview_cam_selection.cpp \
    gui/delegate_line_edit.cpp \
    gui/vertical_box.cpp \
    gui/horizontal_box.cpp \
    logic/data_model_cam_selection.cpp \
    logic/data_model_violation.cpp \
    logic/data_model_camera.cpp \
    gui/listview_camera.cpp \
    gui/listview_camera_object.cpp \
    logic/data_model_camera_object.cpp \
    gui/widget_object_to_cam.cpp \
    logic/data_model_object_type.cpp \
    dbmodule/data_adapter_object_type.cpp \
    gui/combobox_object_type.cpp \
    dbmodule/data_adapter_camera.cpp \
    gui/combobox_camera_search.cpp \
    dbmodule/data_adapter_violation_type.cpp \
    logic/data_model_violation_type.cpp \
    gui/combobox_violation_type.cpp \
    dbmodule/data_adapter_DT.cpp \
    dbmodule/data_adapter_CA.cpp \
    dbmodule/data_adapter_ODH.cpp \
    gui/combobox_violation_object.cpp \
    dbmodule/data_adapter_violation.cpp \
    dbmodule/data_adapter_violation_attachment.cpp \
    gui/widget_tab_setup.cpp \
    dbmodule/data_adapter_import_CA.cpp \
    dbmodule/data_adapter_import_ODH.cpp \
    dbmodule/data_adapter_import_DT.cpp \
    gui/listview_violation_type.cpp \
    gui/combobox_contractor.cpp \
    dbmodule/data_adapter_contractor.cpp \
    logic/data_model_contractor.cpp

HEADERS  += \
    app/application.h \
    app/application_params.h \
    app/application_log.h \
    qt_sqlite/qt_sqlite_dbvalue.h \
    qt_sqlite/qt_sqlite_connection.h \
    qt_sqlite/qt_sqlite_command.h \
    qt_sqlite/qt_data_row.h \
    qt_sqlite/qt_data_parameter.h \
    logic/business_logic.h \
    gui/main_window.h \
    gui/widget_central.h \
    gui/widget_cam_selection.h \
    gui/widget_tab_violation.h \
    gui/widget_tab_object.h \
    gui/widget_violation.h \
    gui/listview_volation.h \
    gui/listview_cam_selection.h \
    gui/delegate_line_edit.h \
    gui/vertical_box.h \
    gui/horizontal_box.h \
    logic/data_model_cam_selection.h \
    logic/data_model_violation.h \
    logic/data_model_camera.h \
    gui/listview_camera.h \
    gui/listview_camera_object.h \
    logic/data_model_camera_object.h \
    gui/widget_object_to_cam.h \
    logic/data_model_object_type.h \
    dbmodule/data_adapter_object_type.h \
    gui/combobox_object_type.h \
    dbmodule/data_adapter_camera.h \
    gui/combobox_camera_search.h \
    dbmodule/data_adapter_violation_type.h \
    logic/data_model_violation_type.h \
    gui/combobox_violation_type.h \
    dbmodule/data_adapter_DT.h \
    dbmodule/data_adapter_CA.h \
    dbmodule/data_adapter_ODH.h \
    dbmodule/data_violation_object.h \
    gui/combobox_violation_object.h \
    dbmodule/data_adapter_violation.h \
    dbmodule/data_adapter_violation_attachment.h \
    gui/widget_tab_setup.h \
    dbmodule/data_adapter_import_CA.h \
    dbmodule/data_adapter_import_ODH.h \
    dbmodule/data_adapter_import_DT.h \
    gui/listview_violation_type.h \
    gui/combobox_contractor.h \
    dbmodule/data_adapter_contractor.h \
    logic/data_model_contractor.h

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
#win32: {
#INCLUDEPATH += W:/sqlite3/include
#LIBS += W:/sqlite3/sqlite3.dll
#RC_FILE = res/winres/app_icon.rc
#}

#rele Chromium OS VM setiings
win32: {
INCLUDEPATH += D:/DEVELOP/sqlite3/include
LIBS += D:/DEVELOP/sqlite3/sqlite3.dll
RC_FILE = res/winres/app_icon.rc
}

OTHER_FILES += \
    sql/TABLE_VIOLATION_ALTER.sql \
    sql/t_violation_attachment.sql \
    sql/t_contractor.sql \
    sql/db_vcam.sql \
    todo.txt \
    sql/TABLE_VIOLATION_ALTER_20150218.sql
