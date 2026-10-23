
#include "gnl_internal.h"
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>

static t_gnl state = { -1, NULL, 0, 0, NULL };

void get_next_line_clear(int fd)
{
    if (state.fd != fd) return;
    free(state.buffer);
    state = (t_gnl){ -1, NULL, 0, 0, NULL };
}

void get_next_line_clear_all(void) { get_next_line_clear(state.fd); }

char *get_next_line(int fd)
{
    char *line;
    int saved_errno;

    if (fd < 0 || BUFFER_SIZE <= 0 || (uintmax_t)BUFFER_SIZE > SIZE_MAX / 2) {
        errno = EINVAL; return (NULL);
    }
    if (state.fd != fd) { get_next_line_clear_all(); state.fd = fd; }
    errno = 0;
    line = gnl_read(&state);
    if (!line) {
        saved_errno = errno;
        get_next_line_clear_all(); errno = saved_errno;
    }
    return (line);
}
