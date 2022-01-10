# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hel-ayac <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/09 17:37:35 by hel-ayac          #+#    #+#              #
#    Updated: 2022/01/09 17:37:37 by hel-ayac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
FLAGS = -Wall -Wextra -Werror
SRCS = philo.c \
		handler.c \
		parsing.c \
		tools.c

OBJ = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	gcc $(FLAGS) $(OBJ) -o $(NAME) -lpthread

%.o : %.c
	gcc -c $(FLAGS) $<

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re :  fclean all
