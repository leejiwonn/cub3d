#include "parse.h"

void free_data(t_parse *data)
{
    int i;

    i = 0;
    if (data->map)
    {
        while (data->map[i])
            free(data->map[i++]);
        free(data->map);
        i = 0;
    }
    if (data->texture)
    {
        while (data->texture[i])
            free(data->texture[i++]);
        free(data->texture);
        i = 0;
    }
}

int get_flag(char *line)
{
    while (*line == ' ')
        line++;
    if (*line == 'N' && *(line + 1) == 'O' && *(line + 2) == ' ')
        return (FLAG_NO);
    else if (*line == 'S' && *(line + 1) == 'O' && *(line + 2) == ' ')
        return (FLAG_SO);
    else if (*line == 'W' && *(line + 1) == 'E' && *(line + 2) == ' ')
        return (FLAG_WE);
    else if (*line == 'E' && *(line + 1) == 'A' && *(line + 2) == ' ')
        return (FLAG_EA);
    else if (*line == 'F' && *(line + 1) == ' ')
        return (FLAG_F);
    else if (*line == 'C' && *(line + 1) == ' ')
        return (FLAG_C);
    return (FLAG_NOT);
}

int is_full(char *flags)
{
    int i;

    i = 0;
    while (i < 6)
    {
        if (flags[i++] == 0)
            return (0);
    }
    return (1);
}

void ft_memset(void *s, int c, size_t n)
{
    size_t i;

    i = 0;
    while (i < n)
        ((unsigned char *)s)[i++] = (unsigned char)c;
}