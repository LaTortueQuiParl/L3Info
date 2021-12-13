QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ajoutcontactdialog.cpp \
    ajoutinteractiondialog.cpp \
    contact.cpp \
    gestioncontacts.cpp \
    gestioninteractions.cpp \
    gestiontodos.cpp \
    interaction.cpp \
    main.cpp \
    mainwindow.cpp \
    todo.cpp \
    date.cpp \
    gestionbdd.cpp

HEADERS += \
    ajoutcontactdialog.h \
    ajoutinteractiondialog.h \
    contact.h \
    gestioncontacts.h \
    gestioninteractions.h \
    gestiontodos.h \
    mainwindow.h \
    interaction.h \
    todo.h \
    date.h \
    gestionbdd.h

FORMS += \
    ajoutcontactdialog.ui \
    ajoutinteractiondialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
