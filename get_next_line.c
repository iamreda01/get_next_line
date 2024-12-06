#include "get_next_line.h"
#include <stdio.h>

int    nline(char *data)
{
    int     i;

    i = 0;
    while (data[i] && data[i] != '\n')
        i++;
    if (data[i] == '\n')
        i++;
    return (i);
}
char    *read_fd(int fd, char *data)
{
    int     byte;
    char    *tmp;

    if (!data)
        data = calloc(1, 1);
    tmp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
    byte = 1;
    while (byte > 0 && !ft_strchr(tmp, '\n'))
    {
        byte = read(fd, tmp, BUFFER_SIZE);
        if (byte < 0)
        {
            free(data);
            free(tmp);
            return (NULL);
        }
        tmp[byte] = '\0';
        data = ft_strjoin(data, tmp);
    }
    free(tmp);
    return (data);
}

char    *extract_line(char *data)
{
    char    *line;
    int     i;

    i = nline(data);
    line = calloc(i + 1, sizeof(char));
    ft_memcpy(line, data, i);
    line[i] = '\0';
    return (line);
}

char    *update_line(char *data)
{
    int i;
    int s;
    char    *update;

    s = 0;
    i = nline(data);
    if (!data[i])
        return (free(data), NULL);
    update = calloc(ft_strlen(data)- i + 1, sizeof(char));
    while (data[i])
        update[s++] = data[i++];
    update[s++] = '\0';
    free(data);
    return (update);
}
char *get_next_line(int fd)
{
    static char     *data;
    char            *line;

    if (fd < 0 || BUFFER_SIZE <= 0 )
        return (NULL);
    data = read_fd(fd, data);
    if (!data)
        return (NULL);
    line = extract_line(data);
    data = update_line(data);
    return (line);
}
// #include <fcntl.h>
// int main ()
// {
//     int fd;
//     fd = open("file", O_RDWR);
//     printf("%s", get_next_line(fd));
//     printf("%s", get_next_line(fd));
//     printf("%s", get_next_line(fd));
// }