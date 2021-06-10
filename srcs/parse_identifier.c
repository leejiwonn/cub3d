#include "parse.h"

static char *set_wall_texture(t_parse *data, char *line, int flag)
{
    if (!set_wall_texture_path(data->texture + flag, &line))
        return ("set_wall_texture_path malloc failed");
    if (*line)
        return ("invalid wall_path");
    return (0);
}

static char *set_color(t_parse *data, char *line, int flag)
{
    int count;
    int color_value;
    char *color_ptr;
    int i;

    count = 0;
    color_ptr = (char *)((data->color) + flag - 4);
    i = 0;
    while (i < 3)
    {
        color_value = 0;
        count += parse_atoi(&line, &color_value);
        if (color_value > 255)
            return ("invalid color");
        *(color_ptr + i + 1) = (char)color_value;
        i++;
    }
    if (count != 2 || *line)
        return ("invalid color");
    return (0);
}

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

char *set_identifier(t_parse *data, char *line, int flag)
{
    char *line_cur;
    char *error_msg;

    line_cur = line;
    error_msg = 0;
    while (*line_cur == ' ')
        line_cur++;
    while (*line_cur != ' ')
        line_cur++;
    while (*line_cur == ' ')
        line_cur++;
    if (FLAG_NO <= flag && flag <= FLAG_EA)
        error_msg = set_wall_texture(data, line_cur, flag);
    else if (flag == FLAG_F || flag == FLAG_C)
        error_msg = set_color(data, line_cur, flag);
    free(line);
    return (error_msg);
}