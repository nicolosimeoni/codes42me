
#include "gnl_internal.h"
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>

/* Doubling avoids repeatedly copying an entire growing line. */
static int append(char **line, size_t *len, size_t *cap,
                  const char *src, size_t n)
{
    size_t required, next, i;
    char *replacement;

    if (*len == SIZE_MAX || n > SIZE_MAX - *len - 1) {
        errno = ENOMEM; return (-1);
    }
    required = *len + n + 1;
    if (required > *cap) {
        next = *cap ? *cap : 64;
        while (next < required) {
            if (next > SIZE_MAX / 2) { next = required; break; }
            next *= 2;
        }
        replacement = malloc(next);
        if (!replacement) return (-1);
        for (i = 0; i < *len; ++i) replacement[i] = (*line)[i];
        free(*line); *line = replacement; *cap = next;
    }
    for (i = 0; i < n; ++i) (*line)[*len + i] = src[i];
    *len += n; (*line)[*len] = '\0';
    return (0);
}

char *gnl_read(t_gnl *state)
{
    char *line = NULL;
    size_t len = 0, cap = 0, start;
    ssize_t n;

    if (!state->buffer) {
        state->buffer = malloc((size_t)BUFFER_SIZE);
        if (!state->buffer) return (NULL);
    }
    while (1) {
        if (state->pos == state->end) {
            do { n = read(state->fd, state->buffer, (size_t)BUFFER_SIZE); }
            while (n < 0 && errno == EINTR);
            if (n < 0) { free(line); return (NULL); }
            if (n == 0) { errno = 0; return (line); }
            state->pos = 0; state->end = (size_t)n;
        }
        start = state->pos;
        while (state->pos < state->end && state->buffer[state->pos] != '\n')
            ++state->pos;
        if (state->pos < state->end) ++state->pos;
        if (append(&line, &len, &cap, state->buffer + start,
                   state->pos - start) < 0) { free(line); return (NULL); }
        if (len && line[len - 1] == '\n') return (line);
    }
}
