# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/23 16:47:12 by kscordel          #+#    #+#              #
#    Updated: 2023/06/23 16:52:33 by kscordel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

# sources
SRCDIR = src/
OBJDIR = obj/
SRCS = $(SRCDIR)philosopher.c
OBJS = $(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(SRCS))

NAME = philosopher

LIBPATH = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) | lib
	$(CC) $(CFLAGS) $(OBJS) $(LIBPATH) -o $@

lib:
	@make -C ./libft

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
		rm -f $(NAME)
		make fclean -C ./libft
	
re: fclean all

.PHONY: all lib clean fclean re