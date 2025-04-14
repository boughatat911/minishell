// #ifndef GET_NEXT_LINE_H
// #define GET_NEXT_LINE_H
// #endif
#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif
int    ft_strlen(char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return (i);
}

char *ft_strchr(char *s, char c)
{
    while (*s)
    {
        if (*s == c)
            return (s);
        s++;
    }
    return (NULL);
}

int ft_strlcpy(char *dst, char *src, int dst_len)
{
    int i = 0;
    int src_len = ft_strlen(src);
    if (dst_len > 0)
    {
        while (i < src_len && i < dst_len - 1)
        {
            dst[i] = src[i];
            i++; 
        }
        dst[i] = '\0';
    }
    return (src_len);
}

char *ft_strdup(char *s)
{
    char *new = malloc (ft_strlen(s) + 1);
    ft_strlcpy(new, s, ft_strlen(s) + 1);
    return (new);
}

char *ft_strjoin(char *s1, char *s2)
{
    char *new = malloc (ft_strlen(s1) +  ft_strlen(s2) + 1);
    ft_strlcpy(new, s1, ft_strlen(s1) + 1);
    ft_strlcpy((new + ft_strlen(s1)), s2, ft_strlen(s2) + 1);
    free(s1);
    return (new);
}
char    *get_next_line(int fd)
{
    static char    buf[BUFFER_SIZE + 1];
    char        *line;
    char        *new_line;
    int            countread;
    int            to_copy;

    line = ft_strdup(buf);
    while (!ft_strchr(line, '\n') && (countread = read(fd, buf, BUFFER_SIZE)) > 0)
    {
        buf[countread] = '\0';
        line = ft_strjoin(line, buf);
    }
    if (!ft_strlen(line))
        return (free(line), NULL);
    new_line = ft_strchr(line, '\n');
    if (new_line != NULL)
    {
        to_copy = new_line - line + 1;
        ft_strlcpy(buf, new_line + 1, BUFFER_SIZE + 1);
    }
    else
    {
        to_copy = ft_strlen(line);
        ft_strlcpy(buf, "", BUFFER_SIZE + 1);
    }
    line[to_copy] = '\0';
    return (line);
}