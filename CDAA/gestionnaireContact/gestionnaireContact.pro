QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    contact.cpp \
    interaction.cpp \
    main.cpp \
    mainwindow.cpp \
    lescontacts.cpp \
    lesinteractions.cpp \
    lestodos.cpp \
    todo.cpp \
    date.cpp

HEADERS += \
    contact.h \
    mainwindow.h \
    lescontacts.h \
    interaction.h \
    lesinteractions.h \
    lestodos.h \
    todo.h \
    date.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
