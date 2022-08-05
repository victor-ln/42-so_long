# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/27 15:34:57 by vlima-nu          #+#    #+#              #
#    Updated: 2021/10/27 15:53:31 by vlima-nu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	so_long

CC			=	clang

MLX			=	./mlx/libmlx.a
LIB			=	./libft/libft.a

FLAGS		=	-Wall -Werror -Wextra -g3 -O3
LINKS		=	-lbsd -lX11 -lXext
INC			=	-I ./mlx -I ./inc -I ./libft

SRC_DIR		=	./src
OBJ_DIR		=	./obj

FILES		=	arrows.c \
				draw_game.c \
				end_game.c \
				enemy.c \
				events.c \
				game.c \
				load_environment.c \
				load_map.c \
				map_init.c \
				map_validate.c \
				so_long.c \
				window.c \

SRC			=	$(addprefix $(SRC_DIR)/, $(FILES))
OBJ			=	$(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

all:		$(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p obj
	$(CC) $(FLAGS) $(INC) -c $< -o $@

$(NAME):	$(MLX) $(LIB) $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) $(MLX) $(LIB) $(LINKS) $(INC) -o $(NAME)
	@echo "Game created!"

$(LIB):
	make -C libft

$(MLX):
	@echo "Compiling Mlx [ .. ]"
	@make -C ./mlx
	@echo "Mlx is ready! [ OK ]"

clean:
	@make -C ./mlx clean
	@make -C ./libft clean
	@rm -fr obj
	@echo "Objects files deleted."

fclean:		clean
	@rm -f $(NAME)
	@make -C ./libft fclean
	@echo "Executable deleted."

bonus:		$(NAME)

norm:
	norminette src inc libft

re:			fclean all

.PHONY: all, clean, fclean, bonus, re
