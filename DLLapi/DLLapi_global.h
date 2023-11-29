#ifndef DLLAPI_GLOBAL_H
#define DLLAPI_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DLLAPI_LIBRARY)
#define DLLAPI_EXPORT Q_DECL_EXPORT
#else
#define DLLAPI_EXPORT Q_DECL_IMPORT
#endif

#endif // DLLAPI_GLOBAL_H
