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
SRCS			=	SRCS/parsing.c \
					UTILS/atoic.c UTILS/split.c \
					main.c
OBJS			=	$(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
DEP				=	$(addprefix $(OBJS_DIR), $(SRCS:.c=.d))

NAME			=	cub3d
HEAD			=	INCLUDES/

CC				=	ccc
RM				=	rm -rf
FLAGS			=	-Wall -Wextra -Werror -lm
FLAGS			+=	-MMD -MP

MLX_NAME		=	libmlx.a
MLX_DIR			=	mlx/
MLX_FLAGS		=	-lXext -lX11 -lm -lz

# RULES -------------------------------------------------------------
all:				mlx $(NAME)

run:				all
					./$(NAME)

$(NAME):			$(OBJS)
					$(CC) $(FLAGS) $(OBJS) $(MLX_DIR)$(MLX_NAME) $(MLX_FLAGS) -o $(NAME)

-include $(DEP)
$(OBJS_DIR)%.o:		%.c | dir
					$(CC) $(FLAGS) -I $(HEAD) -c $< -o $@

dir:
					@mkdir -p $(OBJS_DIR)
					@mkdir -p $(OBJS_DIR)SRCS
					@mkdir -p $(OBJS_DIR)UTILS

mlx:
					make --jobs=3 -C $(MLX_DIR)

clean:
					$(RM) $(OBJS_DIR)
					make clean -C $(MLX_DIR)

fclean:				clean
					$(RM) $(NAME)

re:					fclean all

.PHONY:				all run dir mlx clean fclean re
