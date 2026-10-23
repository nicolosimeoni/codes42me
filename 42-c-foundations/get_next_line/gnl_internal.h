#ifndef GNL_INTERNAL_H
#define GNL_INTERNAL_H
#include "get_next_line.h"
#include <stddef.h>
typedef struct s_gnl {
    int fd;
    char *buffer;
    size_t pos;
    size_t end;
    struct s_gnl *next;
} t_gnl;
char *gnl_read(t_gnl *state);
#endif
