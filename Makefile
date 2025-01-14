# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/04 18:57:22 by fmarin-p          #+#    #+#              #
#    Updated: 2024/01/16 18:44:11 by fmarin-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CFLAGS =		-Wall -Wextra $(WERROR) \
				-I$(INCDIR) -I$(LIBFTDIR) -I$(MINILIBXDIR)include/MLX42
WERROR =		-Werror

LIBFLAGS =	$(MINILIBXDIR)build/libmlx42.a -L$(LIBFTDIR) -lglfw -lft

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	LIBFLAGS += -ldl -pthread -lm
endif

ifeq ($(UNAME_S), Darwin)
	LIBFLAGS += -framework Cocoa -framework OpenGL -framework IOKit \
				-L$(shell which brew)/../../opt/glfw/lib/
endif

SRCDIR =		src/
INITDIR =		init/
OTHERDIR =		other/
GAMEDIR =		game/

INCDIR =		include/
OBJDIR =		obj/
LIBFTDIR =		libft/
MINILIBXDIR =	minilibx/

SRCFILES =	$(addprefix $(INITDIR), initialization.c load_from_file.c check_map.c) \
			$(addprefix $(OTHERDIR), error.c free_mem.c) \
			$(addprefix $(GAMEDIR), raycasting.c mlx.c player.c hooks.c \
			minimap.c minimap_utils.c screen_rendering.c doors.c) \
			main.c
OBJFILES =	$(SRCFILES:.c=.o)
SRCOBJ =	$(addprefix $(OBJDIR), $(OBJFILES))

all: $(NAME)

debug: CFLAGS += -g
debug: WERROR :=
debug: MINILIBXDEBUG := -DDEBUG=1
debug: re
	
$(NAME): $(SRCOBJ)
	@cmake $(MINILIBXDIR) $(MINILIBXDEBUG) -DGLFW_FETCH=1 -B $(MINILIBXDIR)build > /dev/null
	cmake --build $(MINILIBXDIR)build -j4
	$(MAKE) -C $(LIBFTDIR)
	gcc $^ $(LIBFLAGS) -o $@

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)$(INITDIR)
	@mkdir -p $(OBJDIR)$(OTHERDIR)
	@mkdir -p $(OBJDIR)$(GAMEDIR)
	gcc -c $(CFLAGS) $^ -o $@

clean:
	$(MAKE) clean -C $(LIBFTDIR)
	rm -rf $(OBJDIR)
	rm -rf $(MINILIBXDIR)build

fclean: clean
	$(MAKE) fclean -C $(LIBFTDIR)
	rm -rf $(NAME)

re: fclean all

linux-dep:
	@for package in build-essential libx11-dev libglfw3-dev libglfw3 xorg-dev; do \
		if [ $$(apt list --installed 2>/dev/null $$package | wc -l) -eq 1 ]; then \
				sudo apt install $$package; \
		fi; \
	done

mac-dep:
	@if [ -z $(brew list | grep glfw) ]; then \
		brew install glfw; \
	fi;

.PHONY: all clean fclean re