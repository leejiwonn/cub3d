#include "parse.h"

static char *set_wall_texture_path(t_parse *data, char *line, int flag)
{
    if (!new_array(data->texture + flag, &line))
        return ("set_wall_texture_path malloc failed");
    if (*line)
        return ("invalid wall_path");
    return (0);
}

static char *set_color(t_parse *data, char *line, int flag)
{
    int i;
    int tmp;
    int tmp_color;

    i = 0;
    tmp = 0;
    while (i < 3)
    {
        tmp_color = 0;
        tmp += parse_atoi(&line, &tmp_color);
        if (tmp_color > 255)
            return ("invalid color");
        data->color[flag - 4] += tmp_color;
        if (i != 2)
            data->color[flag - 4] = data->color[flag - 4] << 8;
        i++;
    }
    if (tmp != 2 || *line)
        return ("invalid color");
    return (0);
}

char *set_identifier(t_parse *data, char *line, int flag)
{
    char *save;
    char *error;

    save = line;
    error = 0;
    while (*line == ' ')
        line++;
    while (*line != ' ')
        line++;
    while (*line == ' ')
        line++;
    if (flag >= 0 && flag <= 3)
        error = set_wall_texture_path(data, line, flag);
    else if (flag == 4 || flag == 5)
        error = set_color(data, line, flag);
    free(save);
    return (error);
}