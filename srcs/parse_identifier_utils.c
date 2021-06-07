#include "parse.h"

int parse_atoi(char **line, int *target)
{
    int i;
    int check;

    i = 3;
    check = 0;
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
        check = 1;
    }
    while (**line == ' ')
        (*line)++;
    return (check);
}

static int check_length(char *line)
{
    int length;

    length = 0;
    while (*line++)
        length++;
    return (length);
}

int new_array(char **target, char **line)
{
    int tmp;

    *target = malloc(check_length(*line) + 1);
    if (!*target)
        return (0);
    tmp = 0;
    while (**line && **line != ' ')
    {
        *(*target + tmp++) = **line;
        (*line)++;
    }
    *(*target + tmp) = 0;
    return (1);
}