# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yohkim <42.4.yohkim@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/10 14:17:06 by yohkim            #+#    #+#              #
#    Updated: 2022/02/17 16:58:56 by yohkim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS=-Wextra -Wall -Werror
NAME=client

SRCS=client.c \
	client_connect.c \
	client_send.c \

OBJS=$(SRCS:.c=.o)

LIBFT_DIR=../libft
LIBFTFLAG=-lft -L$(LIBFT_DIR)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(LIBFTFLAG) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean : 
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re: fclean all
