#ifndef MAIN_H
#define MAIN_H

#include <math.h>
#include <stdlib.h>
#include "mlx.h"
#include "parse.h"

#define PIT 3.14 / 180

#define WIDTH 0
#define HEIGHT 1
#define RESOL_X 800
#define RESOL_Y 600

typedef struct s_texture
{
    void *image;
    char *addr;
    int bpp;
    int size_line;
    int endian;
    int len[2];
    double ratio[2];
} t_texture;

typedef struct s_player
{
    double pos[2];
    double dir[2];
    double plane[2];
    int key[6];
} t_player;

typedef struct s_dda
{
    int map[2];
    int point[2];
    int side;
    double ray[2];
    double wall_x;
    double sidedist[2];
    double deltadist[2];
    double step[2];
    double walldist;
    t_texture *cur;
} t_dda;

typedef struct s_game
{
    void *mlx;
    void *window;
    void *image;
    char *adr;
    int bpp;
    int leng;
    int endian;
    t_parse *data;
    t_texture **texture;
    t_player *player;
    t_dda *dda;
} t_game;

char *set_game(t_game **game, char *map_path);
char *init_game(t_game **game);
void run_game(t_game *game);
void free_game(t_game *game);

char *set_game_data(t_game *game);

t_texture **set_texture(void *mlx, char **list);
void free_texture(t_texture **texture, void *mlx);
unsigned int texture_color(char *ref, int y, t_texture *texture);

t_player *set_player(int *location, char dir);
char rotate_player(t_player *player, double seta);
char move_ws(t_player *player, char **worldmap, double flag);
char move_ad(t_player *player, char **worldmap, double flag);

int ray_casting(t_game *game, t_player *player, t_parse *data);
unsigned int set_color(char **worldmap, int x, int y, int side);
void draw_point(t_dda *dda, t_parse *data);
char *select_texture(t_texture **texture, t_dda *dda);
void set_dda_value(t_dda *dda, t_player *player, int resolution, int x);
void hit_wall(t_dda *dda, char **map, double *pos);

int key_press(int keycode, t_game *game);
int key_release(int keycode, t_game *game);
int key_exit(t_game *game);
int main_loop(t_game *game);

#endif