# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/15 19:22:08 by jdiaz             #+#    #+#              #
#    Updated: 2018/11/13 12:51:25 by jdiaz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fdf

LIB_PATH	= ./libft/
MLX_PATH	= ./minilibx_macos/

CFLAGS 	= -Wall -Wextra -Werror

SRCS		=	main.c \
	   			draw.c \
				read_file.c \
				press_key.c \
				transformations.c \
				color.c \
				tools.c

OBJS		=	main.o \
	   			draw.o \
				read_file.o \
				press_key.o \
				transformations.o \
				color.o	\
				tools.o

INCLUDE 	=  -I fdf.h -L $(LIB_PATH) -lft -L $(MLX_PATH) -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME):
	@make -C libft
	@echo "\033[32mCompiled libft\033[0m"
	@make -C $(MLX_PATH)
	@echo "\033[32mCompiled mlx_macros\033[0m"
	@gcc $(CFLAGS) -c $(SRCS)
	@gcc -o $(NAME) $(INCLUDE) $(OBJS) libft/libft.a
	@echo "\033[32mCompiled fdf\033[0m"
clean:
	@/bin/rm -f $(OBJS)
	@make -C libft clean
	@make -C $(MLX_PATH) clean
	@echo "\033[31;1m libs cleaned\033[0m"

fclean: clean
	@make -C libft fclean
	@make -C $(MLX_PATH) clean
	@rm -f $(NAME)
	@echo "\033[31;1m$(NAME) and libs fcleaned\033[0m"

re: fclean all

dev: 
	@$(CC) $(CCFLAGS) -g -fsanitize=address  $(INCLUDE) $(OBJ) -o $(NAME)
.PHONY: clean
