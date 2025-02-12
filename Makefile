# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/24 22:09:34 by yushsato          #+#    #+#              #
#    Updated: 2025/01/24 22:28:04 by yushsato         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= webserv
CC		= c++
CFLAGS	= -Wall -Wextra -Werror -std=c++98
SRCS	= \
	webserv.cpp
	
OBJS	= $(SRCS:.cpp=.o)
INCLUDE	= -I./

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(INCLUDE)

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

build: all clean

__debug_configure__:
	$(eval CC := c++)
	$(eval CFLAGS += -g -fsanitize=address -pedantic)

debug: __debug_configure__ all

.PHONY: all clean fclean re build debug __debug_configure__