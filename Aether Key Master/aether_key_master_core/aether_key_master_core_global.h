#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(AETHER_KEY_MASTER_CORE_LIB)
#  define AETHER_KEY_MASTER_CORE_EXPORT Q_DECL_EXPORT
# else
#  define AETHER_KEY_MASTER_CORE_EXPORT Q_DECL_IMPORT
# endif
#else
# define AETHER_KEY_MASTER_CORE_EXPORT
#endif
