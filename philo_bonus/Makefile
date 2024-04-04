# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/23 16:47:12 by kscordel          #+#    #+#              #
#    Updated: 2023/09/12 16:53:41 by kscordel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror


# sources
SRC_DIR = src/
OBJ_DIR = obj/

SRCS = $(SRC_DIR)philosopher.c $(SRC_DIR)routine.c $(SRC_DIR)utils.c $(SRC_DIR)monitoring.c \
		$(SRC_DIR)action.c $(SRC_DIR)time.c $(SRC_DIR)init.c

OBJS = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

NAME = philo_bonus

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
