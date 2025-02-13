# **************************************************************************** # #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tomoron <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/28 00:35:01 by tomoron           #+#    #+#              #
#    Updated: 2024/12/03 15:25:19 by tomoron          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HOSTTYPE := $(shell uname -m)_$(shell uname -s)

NAME := libft_malloc_$(HOSTTYPE).so

CC = cc

SRCS_NAMES =	malloc.c \
				malloc_utils.c\
				show_alloc_mem.c\
				free.c\
				realloc.c\
				utils.c\
				env_debug.c\
				program_end.c

SRCS_DIR = srcs

OBJS_DIR := .objs

SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_NAMES))

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS_NAMES:.c=.o))

FLAGS = -Wall -Wextra -Werror -g

LFT = libft/libft.a

LFT_DIR = libft/

all: libft_malloc.so

exec: $(OBJS_DIR) $(NAME) $(LFT)
	$(CC) -o a.out $(FLAGS) main.c $(NAME) $(LFT) 
	$(CC) -o a.out $(FLAGS) main.c -L. -lft_malloc $(LFT) -Wl,-rpath=.

libft_malloc.so: $(NAME)
	ln -sf $(NAME) libft_malloc.so

$(LFT):
	make -j$(shell nproc) -C $(LFT_DIR)

$(NAME): $(OBJS_DIR) $(OBJS) $(LFT)
	$(CC) -shared -o $(NAME) $(OBJS) $(LFT)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(CC) -fPIC $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR) 
	make -C $(LFT_DIR) fclean

fclean: clean
	rm -f $(NAME)
	rm -f libft_malloc.so

re: fclean all


.PHONY: clean all re fclean
