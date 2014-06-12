QT += core gui opengl

TARGET = mySTLViewer

TEMPLATE = app

SOURCES += main.cpp\
           glwidget.cpp \
    mdialog.cpp \
    viewer.cpp

HEADERS += \
    mdialog.h \
    viewer.h \
    glwidget.h

OTHER_FILES += fragmentShader.fsh\
               vertexShader.vsh

RESOURCES += resources.qrc

FORMS += \
    mdialog.ui \
    viewer.ui
