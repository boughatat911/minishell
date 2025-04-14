#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
#    define BUFFER_SIZE 5000000
#endif

#include <unistd.h>
#include <stdlib.h>

char    *ft_strdup(char *str)
{
        int     len = 0;
        while (str[len])
                len++;
        char    *res = malloc(len + 1); 
        len = 0;
        while (str[len])
        {
                res[len] = str[len];
                len++;
        }
        res[len] = 0;
        return res;
}

char    *get_next_line(int fd) 
{
        static char     buffer[7000000];
        static char            line[700000];
        static int      buffer_pos;
        static int      reads_size;
        int             i;

        i = 0;
        if (fd < 0 || BUFFER_SIZE <= 0)
                return NULL;
        while (1)
        {
                if (buffer_pos >= reads_size)
                {   
                        reads_size = read(fd, buffer, BUFFER_SIZE);
                        buffer_pos = 0;
                        if (reads_size <= 0)
                                break ;
                }
                line[i++] = buffer[buffer_pos++];
                if (buffer[buffer_pos - 1] == '\n' || i >= (int)sizeof(line) - 1)
                        break ;
        }
        line[i] = 0;
        if (i == 0)
                return NULL;
        return (ft_strdup(line));
}


#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <limits.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 100
#endif

char    *ft_strdup(char *src)
{
    char    *dest;
    int    i;

    i = 0;
    while (src[i])
        i++;
    dest = (char *)malloc(sizeof(char) * (i + 1));
    i = 0;
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

char    *get_next_line(int fd)
{
    static char    buffer[700000];
    char        line[70000];
    static int    buffer_read;
    static int     buffer_pos;
    int         i;

    i = 0;
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    while (1)
    {
        if (buffer_pos >= buffer_read)
        {
            buffer_read = read(fd, buffer, BUFFER_SIZE);
            buffer_pos = 0;
            if (buffer_read <= 0)
                break ;
        }
        line[i++] = buffer[buffer_pos++];
        if (buffer[buffer_pos - 1] == '\n' || i >= (int)sizeof(line) - 1)
            break ;
    }
    line[i] = '\0';
    if (i == 0)
        return (NULL);
    return (ft_strdup(line));
}