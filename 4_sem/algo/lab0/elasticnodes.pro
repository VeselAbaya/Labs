QT += widgets

HEADERS += \
        edge.h \
        node.h \
        graphwidget.h \
    mainwindow.h \
    about.h \
    insertdialog.h

SOURCES += \
        edge.cpp \
        main.cpp \
        node.cpp \
        graphwidget.cpp \
    mainwindow.cpp \
    about.cpp \
    insertdialog.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/graphicsview/elasticnodes
INSTALLS += target

FORMS += \
    mainwindow.ui \
    about.ui \
    insertdialog.ui

RESOURCES += \
    about.qrc

DISTFILES +=
