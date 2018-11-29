TEMPLATE = app
TARGET = simplebrowser
QT += webenginewidgets
CONFIG += c++11

HEADERS += \
    browser.h \
    browserwindow.h \
    downloadmanagerwidget.h \
    downloadwidget.h \
    tabwidget.h \
    webpage.h \
    webpopupwindow.h \
    webview.h \
    focusmanager.h \
    avl.h \
    EditWindow.h \
    LoginWindow.h

SOURCES += \
    browser.cpp \
    browserwindow.cpp \
    downloadmanagerwidget.cpp \
    downloadwidget.cpp \
    main.cpp \
    tabwidget.cpp \
    webpage.cpp \
    webpopupwindow.cpp \
    webview.cpp \
    focusmanager.cpp \
    avl.cpp \
    EditWindow.cpp \
    LoginWindow.cpp

FORMS += \
    certificateerrordialog.ui \
    passworddialog.ui \
    downloadmanagerwidget.ui \
    downloadwidget.ui \
    EditWindow.ui \
    LoginWindow.ui

RESOURCES += data/simplebrowser.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/webenginewidgets/simplebrowser
INSTALLS += target
