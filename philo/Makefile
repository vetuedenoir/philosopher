# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/23 16:47:12 by kscordel          #+#    #+#              #
#    Updated: 2023/09/11 14:32:02 by kscordel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3


# sources
SRC_DIR = src/
OBJ_DIR = obj/

SRCS = $(SRC_DIR)philosopher.c $(SRC_DIR)routine.c $(SRC_DIR)utils.c $(SRC_DIR)dead_no_eat.c \
		$(SRC_DIR)init.c $(SRC_DIR)time.c $(SRC_DIR)action.c

OBJS = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

NAME = philo

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ -lpthread

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
		rm -f $(NAME)
	
re: fclean all

.PHONY: all lib clean fclean re
