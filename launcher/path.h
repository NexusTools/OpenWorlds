#ifndef PATH_H
#define PATH_H

#include <QtGlobal>

#ifdef Q_OS_UNIX
#define PATH_SEP ':'
#define RELEASE_DIR /* none */
#else
#ifdef DEBUG_BUILD
#define RELEASE_DIR "/debug"
#else
#define RELEASE_DIR "/release"
#endif
#define PATH_SEP ';'
#endif

#endif // PATH_H
