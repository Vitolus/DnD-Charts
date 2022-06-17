QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ctrl/jsonfilepicker.cpp \
    main.cpp \
    mainwindow.cpp \
    model/adminmodel.cpp \
    model/barchartmodel.cpp \
    model/model.cpp \
    model/piechartmodel.cpp \
    model/record.cpp

HEADERS += \
    ctrl/jsonfilepicker.h \
    mainwindow.h \
    model/adminmodel.h \
    model/barchartmodel.h \
    model/model.h \
    model/piechartmodel.h \
    model/record.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
