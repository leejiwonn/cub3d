#include "main.h"

static char *map_path_str(char *str)
{
    int i;
    char *new_str;

    i = 0;
    while (*(str + i))
        i++;
    new_str = malloc(11 + i);
    if (!new_str)
        return (0);
    i = 0;
    while (*str)
        *(new_str + i++) = *str++;
    *(new_str + i) = 0;
    return (new_str);
}

char *set_game(t_game **game, char *map_path)
{
    char *error_msg;

    if ((error_msg = init_game(game)))
        return (error_msg);
    if ((error_msg = parse(&(*game)->data, map_path_str(map_path), 0xc0)))
        return (error_msg);
    return (set_game_data(*game));
}