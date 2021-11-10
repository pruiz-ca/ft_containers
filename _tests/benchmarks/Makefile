# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pruiz-ca <pruiz-ca@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/07 00:18:05 by pruiz-ca          #+#    #+#              #
#    Updated: 2021/09/22 12:58:47 by pruiz-ca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL		=	/bin/bash

NAME		=	a.out

NOCOL		=	\033[0m
ORG			=	\033[0;33m
GRN			=	\033[1;32m
CYN			=	\033[0;36m

SRCS		=	main.cpp benchmarks.cpp
OBJS		=	$(SRCS:.cpp=.o)
HEADER		=	-I.

CXX			=	clang++
CXXFLAGS	=	-std=c++98 $(HEADER) -Wall -Wextra -Werror
DEBUGFLAGS	=	-g -fsanitize=address

MSG_SUCCESS	=	echo -e "$(GRN)=> Success!$(NOCOL)"
MSG_DEBUG	=	echo -e "$(CYN)=> Debug mode ON$(NOCOL)"

all:			$(NAME)

$(NAME):		$(OBJS)
				@$(CXX) $(CXXFLAGS) $^ -o $@
				@$(MSG_SUCCESS)
				@./a.out
				@make fclean

clean:
				@$(RM) $(OBJS)

fclean:			clean
				@$(RM) $(NAME)
				@find . -name ".DS_Store" -delete

re:				fclean all

debug:			CXX += -g -fsanitize=address
debug:			MSG_SUCCESS = $(MSG_DEBUG)
debug:			re

.PHONY:			all clean fclean re debug debugflags
