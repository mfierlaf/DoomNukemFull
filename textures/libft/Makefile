# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/04 15:16:48 by mfierlaf          #+#    #+#              #
#    Updated: 2019/10/30 17:02:05 by mfierlaf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
LIB = ./
FLAGS = -Wall -Wextra -Werror

INCL = incl/
SRC_DIR = ./srcs/
SRC =	ft_isalpha.c ft_putendl_fd.c ft_putstr_fd.c ft_strdup.c ft_strstr.c ft_isdigit.c \
		ft_putchar.c ft_putnbr.c ft_strcat.c ft_strncat.c ft_tolower.c ft_atoi.c ft_isprint.c \
		ft_putchar_fd.c ft_putnbr_fd.c ft_strcmp.c ft_strncmp.c ft_toupper.c ft_isalnum.c \
		ft_itoa.c ft_putendl.c ft_putstr.c ft_strcpy.c ft_strncpy.c ft_isascii.c ft_memset.c \
		ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c \
		ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strnstr.c ft_memalloc.c ft_memdel.c ft_strnew.c \
		ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c \
		ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_lstnew.c \
		ft_freechararray.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c \
		ft_print_table.c ft_sqrt.c ft_strjoin_free.c ft_printf.c get_next_line.c ft_strlcpy.c

FILES = $(addprefix $(SRC_DIR),$(SRC))
OBJ_DIR = ./obj/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all : $(NAME)

$(NAME) : $(OBJ)
	@ar -rc $(NAME) $(OBJ)
	@echo "[LIBFT] libft compiled."

$(OBJ_DIR)%.o: srcs/%.c
	@mkdir -p $(dir $@) && gcc $(FLAGS) -c $< -o $@

clean :
	@echo "[LIBFT] Removing .o files."
	@rm -rf $(OBJ_DIR)

fclean : clean
	@echo "[LIBFT] Removing binary file."
	@rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
