#include "parse.h"

void free_data(t_parse *data)
{
    int i;

    i = 0;
    if (data->worldmap)
    {
        while (data->worldmap[i])
            free(data->worldmap[i++]);
        free(data->worldmap);
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

int check_flag(char *line)
{
    while (*line == ' ')
        line++;
    if (*line == 'N' && *(line + 1) == 'O' && *(line + 2) == ' ')
        return (0);
    else if (*line == 'S' && *(line + 1) == 'O' && *(line + 2) == ' ')
        return (1);
    else if (*line == 'W' && *(line + 1) == 'E' && *(line + 2) == ' ')
        return (2);
    else if (*line == 'E' && *(line + 1) == 'A' && *(line + 2) == ' ')
        return (3);
    else if (*line == 'F' && *(line + 1) == ' ')
        return (4);
    else if (*line == 'C' && *(line + 1) == ' ')
        return (5);
    return (7);
}