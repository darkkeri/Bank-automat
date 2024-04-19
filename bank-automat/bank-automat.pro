QT += core gui
QT += network serialport widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bankwindow.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    bankwindow.h \
    mainwindow.h

FORMS += \
    bankwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# win32: LIBS += -L$$PWD/../EXE_TEST/EXE_DLL/build/debug/ -lEXE_DLL

# INCLUDEPATH += $$PWD/../EXE_TEST/EXE_DLL
# DEPENDPATH += $$PWD/../EXE_TEST/EXE_DLL

DISTFILES += \
    styles/myStyle.qss

RESOURCES += \
    resources.qrc

win32: LIBS += -L$$PWD/RFID_DLL/build/debug/ -lRFID_DLL

INCLUDEPATH += $$PWD/RFID_DLL
DEPENDPATH += $$PWD/RFID_DLL

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/RestDLL/build/release/ -lRestDLL
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/RestDLL/build/debug/ -lRestDLL

INCLUDEPATH += $$PWD/RestDLL
DEPENDPATH += $$PWD/RestDLL
