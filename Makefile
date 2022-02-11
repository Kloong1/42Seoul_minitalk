# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yohkim <42.4.yohkim@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/10 14:17:06 by yohkim            #+#    #+#              #
#    Updated: 2022/02/10 14:23:43 by yohkim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS=-Wextra -Wall -Werror
NAME=minitalk

SERVER_SRCS=server.c
CLIENT_SRCS=client.c

OBJS=$(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	cd ./libft && $(MAKE)

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean : 
	rm -rf $(OBJS) $(BONUS_OBJS)

fclean : clean
	rm -rf $(NAME)

re: fclean all

bonus: $(NAME) $(BONUS_OBJS)
	ar -rc $(NAME) $(BONUS_OBJS)
