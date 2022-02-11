# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yohkim <yohkim@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/05 19:23:46 by yohkim            #+#    #+#              #
#    Updated: 2021/07/08 15:51:41 by yohkim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS=-Wextra -Wall -Werror
NAME=libft.a

SRCS=$(addsuffix .c, ft_atoi \
	 				ft_bzero \
					ft_calloc \
	 				ft_isalnum \
	 				ft_isalpha \
					ft_isascii \
					ft_isdigit \
					ft_isprint \
					ft_memchr \
					ft_memcmp \
					ft_memcpy \
					ft_memmove \
					ft_memset \
					ft_strchr \
					ft_strdup \
					ft_strtrim \
					ft_strjoin \
					ft_strlcpy \
					ft_strlen \
					ft_strlcat \
					ft_strncmp \
					ft_strnstr \
					ft_strrchr \
					ft_substr \
					ft_tolower \
					ft_toupper \
					ft_split \
					ft_itoa \
					ft_strmapi \
					ft_striteri \
					ft_putchar_fd \
					ft_putstr_fd \
					ft_putendl_fd \
					ft_putnbr_fd \
)

BONUS_SRCS = $(addsuffix .c, ft_lstnew \
			 				ft_lstadd_front \
							ft_lstsize \
							ft_lstlast \
							ft_lstadd_back \
							ft_lstdelone \
							ft_lstclear \
							ft_lstiter \
							ft_lstmap \
)

OBJS=$(SRCS:.c=.o)

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	ar -rc $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean : 
	rm -rf $(OBJS) $(BONUS_OBJS)

fclean : clean
	rm -rf $(NAME)

re: fclean all

bonus: $(NAME) $(BONUS_OBJS)
	ar -rc $(NAME) $(BONUS_OBJS)
