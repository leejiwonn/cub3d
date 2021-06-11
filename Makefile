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
				parse_identifier.c \
				parse_map_validation.c \
				parse_map.c \
				parse_utils.c \
				parse.c \
				raycasting.c \
				raycasting_utils.c
SRCS		= $(addprefix $(SRCS_DIR)/, $(SRCS_NAME))
OBJS		= $(SRCS:.c=.o)

BONUS_SRCS_DIR	= ./srcs_bonus
BONUS_SRCS_NAME	= main_bonus.c \
				event_key_bonus.c \
				set_game_data_bonus.c \
				set_game_player_bonus.c \
				set_game_texture_bonus.c \
				game_bonus.c \
				get_next_line_bonus.c \
				get_next_line_utils_bonus.c \
				main_bonus.c \
				parse_identifier_bonus.c \
				parse_map_validation_bonus.c \
				parse_map_bonus.c \
				parse_utils_bonus.c \
				parse_bonus.c \
				raycasting_bonus.c \
				raycasting_utils_bonus.c

BONUS_SRCS		= $(addprefix $(BONUS_SRCS_DIR)/, $(BONUS_SRCS_NAME))
BONUS_OBJS		= $(BONUS_SRCS:.c=.o)

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror $(HEADER) -g3 -fsanitize=address
RM			= rm -rf

TEST_FILE	= beach.cub
BONUS_TEST_FILE	= beach_b.cub

all :		$(NAME)

$(NAME) :	$(OBJS)
			make -C minilibx
			cp minilibx/libmlx.dylib libmlx.dylib
			$(CC) $(CFLAGS) $^ libmlx.dylib -o $@

bonus	: 	$(BONUS_OBJS)
			make -C minilibx
			cp minilibx/libmlx.dylib libmlx.dylib
			$(CC) $(CFLAGS) $^ libmlx.dylib -o $(NAME)

clean :
			$(RM) $(OBJS) $(BONUS_OBJS)

fclean :	clean
			make clean -C minilibx
			$(RM) $(NAME) libmlx.dylib

re :		fclean all

testb:
	make bonus
	./$(NAME) $(TEST_FILE)

test:
	make
	./$(NAME) $(BONUS_TEST_FILE)