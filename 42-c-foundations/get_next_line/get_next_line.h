#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif
char *get_next_line(int fd);
/* Release unread buffered data before closing/reusing a descriptor early. */
void get_next_line_clear(int fd);
void get_next_line_clear_all(void);
#endif
