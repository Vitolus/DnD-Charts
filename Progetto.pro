QT += core charts gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ctrl/adminctrl.cpp \
    ctrl/barchartctrl.cpp \
    ctrl/ctrl.cpp \
    ctrl/jsonfilepicker.cpp \
    ctrl/piechartctrl.cpp \
    ctrl/scatterchartctrl.cpp \
    main.cpp \
    mainwindow.cpp \
    model/adminmodel.cpp \
    model/barchartmodel.cpp \
    model/model.cpp \
    model/piechartmodel.cpp \
    model/record.cpp \
    model/scatterchartmodel.cpp \
    view/adminview.cpp \
    view/barchartview.cpp \
    view/homeview.cpp \
    view/piechartoview.cpp \
    view/piechartview.cpp \
    view/scatterchartview.cpp \
    view/view.cpp

HEADERS += \
    ctrl/adminctrl.h \
    ctrl/barchartctrl.h \
    ctrl/ctrl.h \
    ctrl/jsonfilepicker.h \
    ctrl/piechartctrl.h \
    ctrl/scatterchartctrl.h \
    mainwindow.h \
    model/adminmodel.h \
    model/barchartmodel.h \
    model/model.h \
    model/piechartmodel.h \
    model/record.h \
    model/scatterchartmodel.h \
    view/adminview.h \
    view/barchartview.h \
    view/homeview.h \
    view/piechartoview.h \
    view/piechartview.h \
    view/scatterchartview.h \
    view/view.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
