#ifndef COMMON_H
#define COMMON_H

#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

extern void print_copyright(int enabled);

// Tracing macros
#define TRACING_PREFIX "# " TRACING_MODULE "> "

#define ENTRY(format, ...)                                              \
    if (debug >= 1)                                                     \
        fprintf(stderr, TRACING_PREFIX "début de " format ":\n", __VA_ARGS__); \
    else (void)0

#define RETURN(status)                                                  \
    do {                                                                \
        if (debug >= 1)                                                 \
            fprintf(stderr, TRACING_PREFIX "fin de %s(). Retour: %d\n", \
                    __func__, (status));                                \
        return (status);                                                \
    } while (0)

#define TRACE(status, syscall, ...)                               \
    do {                                                          \
        if (debug >= 2)                                           \
            fprintf(stderr, TRACING_PREFIX "* " __VA_ARGS__);     \
        (status) = (syscall);                                     \
        int saved_errno = errno;                                  \
        if (debug >= 2)                                           \
            fprintf(stderr, "%d\n", (status));                 \
        errno = saved_errno;                                      \
    } while (0)

#define ERROR(func)                                         \
    fprintf(stderr, TRACING_PREFIX "! erreur %s(): %s (errno = %d)\n", \
            func, strerror(errno), errno);

#define GAI_ERROR(func, err)                                               \
    fprintf(stderr, TRACING_PREFIX "! erreur %s(): %s (err = %d)\n", \
            func, gai_strerror(err), err);

#endif // !COMMON_H
