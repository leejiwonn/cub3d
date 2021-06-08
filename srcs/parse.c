#include "parse.h"

static char init_parse(t_parse **data)
{
    int i;
    char *start;

    if (!(*data = malloc(sizeof(t_parse))))
        return (0);
    if (!((*data)->texture = malloc(sizeof(char *) * 5)))
        return (0);
    if (!((*data)->worldmap = malloc(sizeof(char *) * 21)))
        return (0);
    i = 0;
    while (i < 21)
        *((*data)->worldmap + i++) = 0;
    i = 0;
    while (i < 5)
        (*data)->texture[i++] = 0;
    i = 0;
    start = (char *)(*data)->resol;
    while (i < 36)
        *(start + i++) = 0;
    (*data)->direction = 0;
    (*data)->col_max = 20;
    return (1);
}

static char *set_parse(t_parse *data, char *line, unsigned char *check)
{
    int flag;

    flag = check_flag(line);
    if (*check != 0xff)
    {
        if (!*line)
        {
            free(line);
            return (0);
        }
        if (flag == 7)
            return ("invalid identifier");
        if ((*check >> flag & 1) == 1)
            return ("reduplication identifier");
        *check += (unsigned int)pow(2, flag);
        return (set_identifier(data, line, flag));
    }
    if (!*line && !*data->worldmap)
    {
        free(line);
        return (0);
    }
    return (set_map(data, line));
}

char *parse(t_parse **data, char *map_path, unsigned char check)
{
    int fd;
    int result;
    char *line;
    char *error_msg;

    if (!init_parse(data))
        return ("init_parse failed");
    if ((fd = open(map_path, O_RDONLY)) == -1)
        return ("invalid map path");
    while (1)
    {
        if ((result = get_next_line(fd, &line)) == -1)
            return ("get_next_line failed");
        if (!result && !*line)
            break;
        if ((error_msg = set_parse(*data, line, &check)))
            return (error_msg);
    }
    free(map_path);
    free(line);
    return (resize_map(*data, check));
}