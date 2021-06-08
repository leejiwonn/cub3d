NAME		= cub3d

HEADER		= -I includes -I minilibx

SRCS_DIR	= ./srcs
SRCS_NAME	= main.c \
				event_key.c \
				set_game_data.c \
				set_game_player.c \
				set_game_texture.c \
				game.c \
				get_next_line.c \
				get_next_line_utils.c \
				main.c \
				parse_identifier_utils.c \
				parse_identifier.c \
				parse_map_utils.c \
				parse_map.c \
				parse_utils.c \
				parse.c \
				raycasting.c \
				raycasting_utils.c
SRCS		= $(addprefix $(SRCS_DIR)/, $(SRCS_NAME))
OBJS		= $(SRCS:.c=.o)

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror $(HEADER) -g3 -fsanitize=address
RM			= rm -rf

all :		$(NAME)

$(NAME) :	$(OBJS)
			make -C minilibx
			cp minilibx/libmlx.dylib libmlx.dylib
			$(CC) $(CFLAGS) $^ libmlx.dylib -o $@

clean :
			$(RM) $(OBJS)

fclean :	clean
			make clean -C minilibx
			$(RM) $(NAME) libmlx.dylib

re :		fclean all