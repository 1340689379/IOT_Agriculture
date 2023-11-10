QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    iot.cpp \
    login.cpp \
    main.cpp \
    registerpage.cpp

HEADERS += \
    iot.h \
    login.h \
    registerpage.h

FORMS += \
    iot.ui \
    login.ui \
    registerpage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc \
    images.qrc

ICON += ":/new/prefix1/IOT.svg"
ICON += ":/new/prefix1/close.svg"
