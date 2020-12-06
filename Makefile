# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tde-brit <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/24 14:58:04 by tde-brit          #+#    #+#              #
#    Updated: 2019/11/12 12:04:43 by tde-brit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom-nukem
FLAGS = -Wall -Wextra -Werror

#****************#
# MLX FOR MAC OS #
#****************#

 MLX_DIR = ./minilibx_macos

 MLX = -L$(MLX_DIR) -lmlx -framework OpenGL -framework Appkit


#****************#
# MLX FOR Linux #
#****************#

MLX_DIR_LIN = ./minilibx_linux

MLX_LIN = -L$(MLX_DIR_LIN) -lmlx -lm -lbsd -lX11 -lXext

INCL = ./header/
LIBFT_DIR = ./libft/

SRCS_DIR = ./src/
SRCS =	main.c event.c draw.c tools.c load.c move.c vline.c bmp.c bmp_2.c \
		bmp_3.c expose.c init.c menu.c menu_keys.c shape.c hud.c sprites.c \
		bots.c anim.c loot.c weapon.c skybox.c deco.c load_textures.c menu2.c \
		free.c multi_sprites.c tools2.c tools3.c tools4.c weapon2.c read_map.c \
		draw2.c draw3.c draw4.c game.c sector_malloc.c map_editor.c save_map.c \
		geometry.c

FILES = $(addprefix $(SRCS_DIR),$(SRCS))
OBJS_DIR = ./obj/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

all : $(NAME)

$(NAME) : $(OBJS)
	@echo "Compiling libft"
	@make -C $(LIBFT_DIR)
	@echo "Compiling minilibx"
	@make -C $(MLX_DIR)
	@echo "Creating binary file."
	@gcc $(FLAGS) $(OBJS) -o $(NAME) -L$(LIBFT_DIR) -lft $(MLX)
	@echo "Cleaning libft"

linux : $(OBJS)
	@echo "Compiling libft"
	@make -C $(LIBFT_DIR)
	@echo "Compiling minilibx"
	@make -C $(MLX_DIR_LIN)
	@echo "Creating binary file."
	@gcc -Wall -Wextra $(OBJS) -o $(NAME) -L$(LIBFT_DIR) -lft $(MLX_LIN)
	@echo "Cleaning libft"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@echo "Compiling $@"
	@mkdir -p $(dir $@) && gcc $(FLAGS) -c $< -o $@

clean :
	@echo "Removing .o files."
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)
	@rm -rf $(OBJS_DIR)

fclean : clean
	@echo "Removing binary file."
	@make fclean -C $(LIBFT_DIR)
	@rm -rf $(NAME)

re : fclean all

linuxclean :
	@echo "Removing .o files."
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR_LIN)
	@rm -rf $(OBJS_DIR)

linuxfclean : linuxclean
	@echo "Removing binary file."
	@make fclean -C $(LIBFT_DIR)
	@rm -rf $(NAME)

linuxre : linuxfclean linux
.PHONY : all clean fclean re linux linuxclean linuxfclean linuxre
