# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yohkim <42.4.yohkim@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/10 14:17:06 by yohkim            #+#    #+#              #
#    Updated: 2022/02/22 16:35:22 by yohkim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS=-Wextra -Wall -Werror
NAME=minitalk

SERVER_DIR=./server
CLIENT_DIR=./client
LIBFT_DIR=./libft

all : $(NAME)

$(NAME) :
	cd $(LIBFT_DIR) && $(MAKE)
	cd $(CLIENT_DIR) && $(MAKE)
	cd $(SERVER_DIR) && $(MAKE)

client_binary :
	cd $(LIBFT_DIR) && $(MAKE)
	cd $(CLIENT_DIR) && $(MAKE)

server_binary :
	cd $(LIBFT_DIR) && $(MAKE)
	cd $(SERVER_DIR) && $(MAKE)

clean : 
	cd $(LIBFT_DIR) && $(MAKE) clean
	cd $(CLIENT_DIR) && $(MAKE) clean
	cd $(SERVER_DIR) && $(MAKE) clean

fclean : clean
	cd $(LIBFT_DIR) && $(MAKE) fclean
	cd $(CLIENT_DIR) && $(MAKE) fclean
	cd $(SERVER_DIR) && $(MAKE) fclean

re: fclean all
