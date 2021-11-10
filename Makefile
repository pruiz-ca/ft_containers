# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pruiz-ca <pruiz-ca@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/07 00:18:05 by pruiz-ca          #+#    #+#              #
#    Updated: 2021/11/10 16:44:45 by pruiz-ca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL		=	/bin/bash

NAME		=	a.out

SRC_DIR		=	src/
OBJ_DIR		=	obj/
INC_DIR		=	inc/

NOCOL		=	\033[0m
ORG			=	\033[0;33m
GRN			=	\033[1;32m
CYN			=	\033[0;36m

SRCS		=	main.cpp
OBJS		=	$(SRCS:.cpp=.o)
HEADER		=	-Icontainers -Iiterators -Iutils

CXX			=	clang++
CXXFLAGS	=	-std=c++98 $(HEADER) -Wall -Wextra -Werror
DEBUGFLAGS	=	-g3 -fsanitize=address

MSG_SUCCESS	=	echo -e "$(GRN)=> Success!$(NOCOL)"
MSG_DEBUG	=	echo -e "$(CYN)=> Debug mode ON$(NOCOL)"

all:			$(NAME)

$(NAME):		$(OBJS)
				@$(CXX) $(CXXFLAGS) $^ -o $@
				@$(MSG_SUCCESS)
				@./a.out 42

clean:
				@$(RM) $(OBJS)

fclean:			clean
				@$(RM) $(NAME)
				@find . -name ".DS_Store" -delete
				@find . -name "*.out" -delete
				@find . -name "*.dSYM" -exec rm -R "{}" +

re:				fclean all

debug:			CXX += -g -fsanitize=address
debug:			MSG_SUCCESS = $(MSG_DEBUG)
debug:			re

tests:
				@cd _tests/containers_test && ./do.sh vector stack map set
				@make -C _tests/benchmarks
				@make fclean

.PHONY:			all clean fclean re debug debugflags tests
