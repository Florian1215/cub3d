# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/09 22:01:38 by fguirama          #+#    #+#              #
#    Updated: 2023/05/09 22:01:38 by fguirama         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

# VAR ---------------------------------------------------------------
OBJS_DIR		=	.OBJS/
SRCS			=	SRCS/minimap.c SRCS/player.c SRCS/draw.c \
					SRCS/PARSING/parsing.c SRCS/PARSING/parse_map.c SRCS/PARSING/parse_content.c SRCS/PARSING/check_close_map.c \
					SRCS/HOOK/hook.c SRCS/HOOK/key.c SRCS/HOOK/mouse.c \
					UTILS/STR/str_end_with.c UTILS/STR/str_len.c UTILS/STR/str_str.c UTILS/STR/str_dup.c UTILS/STR/put_str.c \
					UTILS/atoi.c UTILS/get_next_line.c UTILS/split.c UTILS/maths.c UTILS/list.c UTILS/mlx.c UTILS/free.c UTILS/init.c UTILS/error.c \
					main.c
OBJS			=	$(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
DEP				=	$(addprefix $(OBJS_DIR), $(SRCS:.c=.d))

NAME			=	cub3d
HEAD			=	INCLUDES/

CC				=	cc
RM				=	rm -rf
FLAGS			=	-Wall -Wextra -Werror -g3# -fsanitize=address
FLAGS			+=	-MMD -MP

MLX_NAME		=	libmlx.a
MLX_DIR			=	mlx/
MLX_FLAGS		=	-lXext -lX11 -lz

# RULES -------------------------------------------------------------
all:				mlx $(NAME)

run:				all
					./$(NAME) ./MAPS/1/map.cub

$(NAME):			$(OBJS)
					$(CC) $(FLAGS) $(OBJS) $(MLX_DIR)$(MLX_NAME) $(MLX_FLAGS) -o $(NAME)

-include $(DEP)
$(OBJS_DIR)%.o:		%.c | dir
					$(CC) $(FLAGS) -I $(HEAD) -c $< -o $@

dir:
					@mkdir -p $(OBJS_DIR)
					@mkdir -p $(OBJS_DIR)SRCS
					@mkdir -p $(OBJS_DIR)SRCS/PARSING
					@mkdir -p $(OBJS_DIR)SRCS/HOOK
					@mkdir -p $(OBJS_DIR)UTILS
					@mkdir -p $(OBJS_DIR)UTILS/STR

mlx:
					make --jobs=3 -C $(MLX_DIR)

clean:
					$(RM) $(OBJS_DIR)
					make clean -C $(MLX_DIR)

fclean:				clean
					$(RM) $(NAME)

re:					fclean all

.PHONY:				all run dir mlx clean fclean re
