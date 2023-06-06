# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/09 22:01:38 by fguirama          #+#    #+#              #
#    Updated: 2023/05/20 18:56:55 by mfinette         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# VAR ---------------------------------------------------------------
OBJS_DIR		=	.OBJS/
SRCS			=	SRCS/draw.c SRCS/maps.c SRCS/menu.c SRCS/fov.c SRCS/minimap.c SRCS/player.c \
					SRCS/PARSING/open_dir.c SRCS/PARSING/parsing.c SRCS/PARSING/parse_map.c SRCS/PARSING/parse_content.c \
					SRCS/HOOK/hook.c SRCS/HOOK/key.c SRCS/HOOK/mouse.c \
					UTILS/error.c UTILS/tab.c UTILS/free.c UTILS/get_next_line.c UTILS/init.c UTILS/list.c UTILS/map.c UTILS/mlx.c UTILS/split.c \
					UTILS/MATHS/atoi.c UTILS/MATHS/compute.c UTILS/MATHS/pow.c UTILS/MATHS/sqrt.c \
					UTILS/STR/str_dup.c UTILS/STR/str_join.c UTILS/STR/str_end_with.c UTILS/STR/str_len.c UTILS/STR/str_str.c \
					main.c
OBJS			=	$(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
DEP				=	$(addprefix $(OBJS_DIR), $(SRCS:.c=.d))

NAME			=	cub3d
HEAD			=	INCLUDES/

CC				=	cc
RM				=	rm -rf

FLAGS			=	-Wall -Wextra -Werror -g3 -fsanitize=address
FLAGS			+=	-MMD -MP

MLX_NAME		=	libmlx.a

UNAME			=	$(shell uname -s)

ifeq ($(UNAME), Linux)
MLX_DIR			=	mlx/linux/
MLX_FLAGS		=	-lXext -lX11 -lm -lz
endif

ifeq ($(UNAME), Darwin)
MLX_DIR			=	mlx/mac/
MLX_FLAGS		=	-framework OpenGL -framework AppKit
endif

# RULES -------------------------------------------------------------
all:				mlx $(NAME)

run:				all
					./$(NAME) ./MAPS/

norm:
					norminette $(SRCS) $(HEAD)/*.h | grep -E "(Error|Warning)"

$(NAME):			$(OBJS)
					$(CC) $(FLAGS) $(OBJS) $(MLX_DIR)$(MLX_NAME) $(MLX_FLAGS) -lm -o $(NAME)

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
					@mkdir -p $(OBJS_DIR)UTILS/MATHS

mlx:
					make --jobs=3 -C $(MLX_DIR)

clean:
					$(RM) $(OBJS_DIR)
					make clean -C $(MLX_DIR)

fclean:				clean
					$(RM) $(NAME)

re:					fclean all

.PHONY:				all run dir norm mlx clean fclean re
