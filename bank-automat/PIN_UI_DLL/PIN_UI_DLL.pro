QT -= gui
QT += widgets

TEMPLATE = lib
DEFINES += PIN_UI_DLL_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    pin_ui_dll.cpp \
    popup.cpp

HEADERS += \
    PIN_UI_DLL_global.h \
    pin_ui_dll.h \
    popup.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

FORMS += \
    pinui.ui \
    popup.ui
