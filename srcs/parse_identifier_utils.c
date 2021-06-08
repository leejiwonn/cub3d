#include "parse.h"

int parse_atoi(char **line, int *target)
{
    int i;
    int check_comma;

    i = 3;
    check_comma = 0;
    while (**line == '0')
        (*line)++;
    while (**line >= '0' && **line <= '9' && i--)
    {
        *target = (*target * 10) + **line - 48;
        (*line)++;
    }
    while (**line == ' ')
        (*line)++;
    if (**line == ',')
    {
        (*line)++;
        check_comma = 1;
    }
    while (**line == ' ')
        (*line)++;
    return (check_comma);
}

int set_wall_texture_path(char **target, char **line)
{
    int i;

    if (!(*target = malloc(ft_strlen(*line) + 1)))
        return (0);
    i = 0;
    while (**line && **line != ' ')
    {
        *(*target + i++) = **line;
        (*line)++;
    }
    *(*target + i) = 0;
    return (1);
}