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
        *(color_ptr + i) = color_value;
        i++;
    }
    if (count != 2 || *line)
        return ("invalid color");
    return (0);
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