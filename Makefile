# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/27 15:34:57 by vlima-nu          #+#    #+#              #
#    Updated: 2022/10/30 12:42:38 by vlima-nu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	so_long

CC			=	gcc

MLX			=	./minilibx-linux/libmlx.a
LIB			=	./libft/libft.a

MKDIR		=	mkdir -p
MAKEFILE_FLAGS	= --no-print-directory --quiet
FLAGS		=	-Wall -Werror -Wextra -O3
LINKS		=	-lbsd -lX11 -lXext
INC			=	-I ./minilibx-linux -I ./inc -I ./libft

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

ifndef ECHO
	T := $(shell $(MAKE) $(MAKECMDGOALS) -n ECHO="counter" | grep -c "counter")
endif

ifeq ($(firstword $(MAKECMDGOALS)), $(shell echo re))
	T := $(shell expr $(words $(FILES)) + 1)
endif

ITALIC_LIGHTER_YELLOW	= "\e[1;3;33m"
ITALIC_BOLD_GREEN		= "\e[0;3;92m"
RESET_COLOR				= "\e[0m"
PRINT	:=	$(shell which echo) -e

N := x
C = $(words $N)$(eval N := x $N)
P = "`expr $C '*' 100 / $T`"

ECHO = $(PRINT) $(ITALIC_BOLD_GREEN)"[$(P)%]\t"

all:		$(NAME)

$(OBJ_DIR):
	@$(MKDIR) $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(ECHO) Compiling $< $(RESET_COLOR)
	@$(CC) $(FLAGS) $(INC) -c $< -o $@

$(NAME):	$(MLX) $(LIB) $(OBJ_DIR) $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) $(MLX) $(LIB) $(LINKS) $(INC) -o $(NAME)
	@$(ECHO) $(NAME) Created! $(RESET_COLOR)

$(LIB):
	@make $(MAKEFILE_FLAGS) -C libft

$(MLX):
	@echo "Compiling Mlx [ .. ]"
	@make $(MAKEFILE_FLAGS) -C ./minilibx-linux
	@echo "Mlx is ready! [ OK ]"

clean:
	@make $(MAKEFILE_FLAGS) -C ./minilibx-linux clean
	@make $(MAKEFILE_FLAGS) -C ./libft clean
	@rm -fr obj
	@$(PRINT) $(ITALIC_LIGHTER_YELLOW)"Objects deleted" $(RESET_COLOR)

fclean:		clean
	@rm -f $(NAME)
	@make $(MAKEFILE_FLAGS) -C ./libft fclean
	@$(PRINT) $(ITALIC_LIGHTER_YELLOW)$(NAME) "deleted" $(RESET_COLOR)

bonus:		$(NAME)

norm:
	norminette src inc libft

re:			fclean all

.PHONY: all, clean, fclean, bonus, re
