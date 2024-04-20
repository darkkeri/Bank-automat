#ifndef PIN_UI_DLL_GLOBAL_H
#define PIN_UI_DLL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PIN_UI_DLL_LIBRARY)
#define PIN_UI_DLL_EXPORT Q_DECL_EXPORT
#else
#define PIN_UI_DLL_EXPORT Q_DECL_IMPORT
#endif

#endif // PIN_UI_DLL_GLOBAL_H
