#ifndef PARSE_H
#define PARSE_H

#include <fcntl.h>
#include "get_next_line.h"
#include <math.h>
#include <stdio.h>

#define X 0
#define Y 1
#define FLAG_NO 0
#define FLAG_SO 1
#define FLAG_WE 2
#define FLAG_EA 3
#define FLAG_F 4
#define FLAG_C 5
#define FLAG_NOT 6

typedef struct s_color
{
    char r;
    char g;
    char b;
    char a;
} t_color;

typedef struct s_parse
{
    int resol[2]; // [0] = x, [1] = y
    int col_index;
    int map_width;
    int location[2]; // [0] = x, [1] = y
    t_color color[2];
    int col_end;
    char direction;
    char **map;
    char **texture; // texture[0] = NO, [1] = SO, [2] = WE, [3] = EA, [4] = S
} t_parse;

char *parse(t_parse **data, char *map_path);
void free_data(t_parse *data);
int get_flag(char *line);
int is_full(char *flags);
void ft_memset(void *s, int c, size_t n);

char *set_map(t_parse *data, char *line);
char *resize_map(t_parse *data, int check_flags);
char *map_validation(t_parse *data, int max);

char *set_identifier(t_parse *data, char *line, int flag);
int set_wall_texture_path(char **target, char **line);
int parse_atoi(char **line, int *target);

#endif