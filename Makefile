# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/04 18:57:22 by fmarin-p          #+#    #+#              #
#    Updated: 2023/10/04 20:46:04 by fmarin-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CFLAGS = -Wall -Wextra -Werror -I$(INCDIR) -I$(LIBFTDIR)

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CFLAGS += -D LINUX
endif
ifeq ($(UNAME_S),Darwin)
	CFLAGS += -framework Cocoa -framework OpenGL -framework IOKit
endif

SRCFILES = error_msg.c main.c motion_math.c parser_map.c 
OBJFILES = $(SRCFILES:.c=.o)

SRCOBJ = $(addprefix $(OBJDIR), $(OBJFILES))

SRCDIR = src/
INCDIR = include/
OBJDIR = obj/
LIBFTDIR = libft/

all: $(NAME)

debug: CFLAGS += -g
debug: re

$(NAME): $(SRCOBJ)
	$(MAKE) -C $(LIBFTDIR)
	@gcc $^ $(LIBFTDIR)libft.a $(LDFLAGS) -o $@

$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p obj
	gcc -c $(CFLAGS) $^ -o $@

clean:
	$(MAKE) clean -C $(LIBFTDIR)
	rm -rf $(OBJDIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFTDIR)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re