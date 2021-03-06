#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/27 15:23:08 by vlikhotk          #+#    #+#              #
#    Updated: 2017/11/02 15:15:21 by vlikhotk         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = vlikhotk.filler

LIB_DIR = ./libft/

SFILES = main.c find_solve.c
OFILES = main.o find_solve.o

VIZUALIZER = vizualizer
SVIZ = vizualization.c general_funcs.c color_types.c
OVIZ = vizualization.o general_funcs.o color_types.o

LIBFT = $(LIBFT_DIR)libftprintf.a
LIBFT_DIR = $(LIB_DIR)
LIBFT_INC = $(LIBFT_DIR)includes/

CC_FLAGS = -Wall -Wextra -Werror
HEADER_FLAGS = -I $(LIBFT_INC)

CC_FLAGS = -Wall -Wextra -Werror
CC = gcc

all: $(NAME)

$(NAME): $(LIBFT) $(VIZUALIZER) $(OFILES)
	$(CC) $(OFILES) general_funcs.o $(LIBFT) -o $(NAME)

$(OFILES): %.o:%.c
	$(CC) -c $< -o $@ $(CC_FLAGS) $(HEADER_FLAGS)

$(OVIZ): %.o:%.c
	$(CC) -c $(CC_FLAGS) $(SVIZ)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(VIZUALIZER): $(OVIZ)
	$(CC) $(OVIZ) $(LIBFT) -o $(VIZUALIZER)

clean:
	rm -rf $(OFILES) $(OVIZ)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -rf $(NAME) $(VIZUALIZER)
	make fclean -C $(LIBFT_DIR)

re: fclean all
