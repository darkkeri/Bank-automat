#ifndef EXE_DLL_GLOBAL_H
#define EXE_DLL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(EXE_DLL_LIBRARY)
#define EXE_DLL_EXPORT Q_DECL_EXPORT
#else
#define EXE_DLL_EXPORT Q_DECL_IMPORT
#endif

#endif // EXE_DLL_GLOBAL_H
