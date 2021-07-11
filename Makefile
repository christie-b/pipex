# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/09 14:10:47 by cboutier          #+#    #+#              #
#    Updated: 2021/07/09 18:10:12 by cboutier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DIR	= .

SRCS	= pipex.c pipex_utils.c parsing.c ft_split.c paths.c ft_strjoin.c


OBJS	= ${SRCS:.c=.o}

NAME		= pipex

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

RM			= rm -f

.c.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

${NAME}:	${OBJS}

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean