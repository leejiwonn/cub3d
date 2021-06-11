/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonlee <jiwonlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 02:45:03 by jiwonlee          #+#    #+#             */
/*   Updated: 2021/06/12 02:45:46 by jiwonlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_BONUS_H
# define MAIN_BONUS_H

# include <math.h>
# include <stdlib.h>
# include "mlx.h"
# include "parse_bonus.h"

# define PI 3.14
# define HALF_CYCLE 180

# define MOVE_SCALE 0.3

# define UP 0
# define DOWN 1
# define C 1
# define F 0
# define WIDTH 0
# define HEIGHT 1
# define RESOL_X 800
# define RESOL_Y 600

# define MINIMAP_COLOR_SPACE 0x0091e0f4
# define MINIMAP_COLOR_WALL 0x000c90ad
# define MINIMAP_COLOR_DOOR 0x00b7b7b7
# define MINIMAP_COLOR_ROAD 0x00f8f1f9
# define MINIMAP_COLOR_PLAYER 0x000c90ad

# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
# define KEY_SPACE 49
# define KEY_ESC 53
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_P 35

# define A 0
# define S 1
# define D 2
# define W 3
# define LEFT 4
# define RIGHT 5
# define MOUSE_MOVE 6
# define SPACE 7
# define MOUSE_TOGGLE 8

# define SCALE 10

typedef struct		s_texture
{
	void			*image;
	char			*addr;
	int				bpp;
	int				size_line;
	int				endian;
	int				len[2];
	double			ratio_y;
}					t_texture;

typedef struct		s_minimap
{
	int				y;
	int				x;
	char			*img;
	unsigned int	*cur_img_ptr;
	unsigned int	*line;
	t_texture		texture;
}					t_minimap;

typedef struct		s_player
{
	double			pos[2];
	double			dir[2];
	double			plane[2];
	int				key[9];
	int				mouse_x;
}					t_player;

typedef struct		s_dda
{
	int				pos_to_int[2];
	int				point[2];
	int				side;
	double			ray[2];
	double			wall_x;
	double			sidedist[2];
	double			deltadist[2];
	double			step[2];
	double			walldist;
	t_texture		*cur;
}					t_dda;

typedef struct		s_game
{
	void			*mlx;
	void			*window;
	void			*image;
	char			*addr;
	int				bpp;
	int				size_line;
	int				endian;
	t_parse			*data;
	t_texture		**texture;
	t_texture		door;
	t_minimap		minimap;
	t_player		*player;
	t_dda			*dda;
}					t_game;

char				*set_game(t_game *game, char *map_path);
char				*init_game(t_game **game);
void				run_game(t_game *game);
int					free_game(t_game *game);
int					free_game_exit(t_game *game, char *message);

char				*set_game_data(t_game *game);

t_texture			**set_texture(void *mlx, char **list);
void				free_texture(t_texture **texture, void *mlx);
int					set_texture_data(void *mlx, char *path,
		t_texture *texture_info);

t_player			*set_player(int *location, char dir);
char				rotate_player(t_player *player, double seta);
char				move_ws(t_player *player, char **worldmap, double scale);
char				move_ad(t_player *player, char **worldmap, double scale);

int					ray_casting(t_game *game, t_player *player, t_parse *data);
unsigned int		set_color(char **worldmap, int x, int y, int side);
void				set_point(t_dda *dda, t_parse *data);
char				*get_texture_start(t_texture **texture,
		t_dda *dda, t_game *game);
void				set_dda_value(t_dda *dda, t_player *player,
		int resolution, int x);
void				hit_wall(t_dda *dda, char **map, double *pos);

int					key_press(int keycode, t_game *game);
int					key_release(int keycode, t_game *game);
int					key_exit(t_game *game);
int					main_loop(t_game *game);

int					is_door_pos(int x, int y, t_game *game);
t_door_list			*create_door_list(int x, int y);
void				free_list(t_door_list *head);
void				add_list(t_door_list **head, t_door_list *new_list);

int					rotate_mouse(t_game *game);
int					proc_mouse_event(int x, int y, t_game *game);

#endif
