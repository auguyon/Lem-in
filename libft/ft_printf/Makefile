# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ftrujill <ftrujill@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/29 13:27:24 by ftrujill          #+#    #+#              #
#    Updated: 2019/06/22 12:55:37 by ftrujill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = gcc
CC_FLAGS = -Wall -Werror -Wextra

OBJ_DIR = objects

SRC_PATH = ./sources/
OBJ_PATH = ./$(OBJ_DIR)/
INC_PATH = ./includes/
LFT_PATH = ./

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix $(INC_PATH),$(INC_NAME))

OBJ_NAME = $(SRC_NAME:.c=.o)

INC_NAME = libft.h ft_printf.h conversions.h

SRC_NAME = ft_printf.c get_arg.c aux_print.c aux.c conversions_1.c conversions_2.c conversions_3.c\
ft_index_rev.c\
ft_itoa_base.c\
ft_strlower.c\
ft_max_int.c\
ft_min_int.c\
ft_max.c\
ft_min.c\
ft_lstdelnext.c\
ft_realloc.c\
ft_memindex.c\
ft_memjoin_alloc.c\
ft_memjoin_allocf.c\
ft_atoi.c\
ft_bzero.c\
ft_index.c\
ft_index_uc.c\
ft_isalnum.c\
ft_isalpha.c\
ft_isascii.c\
ft_isdigit.c\
ft_isprint.c\
ft_itoa.c\
ft_lstadd.c\
ft_lstdel.c\
ft_lstdelone.c\
ft_lstiter.c\
ft_lstmap.c\
ft_lstnew.c\
ft_lstprt.c\
ft_memalloc.c\
ft_memccpy.c\
ft_memchr.c\
ft_memcmp.c\
ft_memcpy.c\
ft_memdel.c\
ft_memlap_fwd.c\
ft_memmove.c\
ft_memnlap_fwd.c\
ft_memset.c\
ft_print_params.c\
ft_print_tab.c\
ft_putchar.c\
ft_putchar_fd.c\
ft_putendl.c\
ft_putendl_fd.c\
ft_putnbr.c\
ft_putnbr_fd.c\
ft_putnstr.c\
ft_putstr.c\
ft_putstr_fd.c\
ft_strcat.c\
ft_strchr.c\
ft_strclr.c\
ft_strcmp.c\
ft_strcpy.c\
ft_strdel.c\
ft_strdup.c\
ft_strequ.c\
ft_strrev.c\
ft_striter.c\
ft_striteri.c\
ft_strjoin.c\
ft_strlcat.c\
ft_strlen.c\
ft_strmap.c\
ft_strmapi.c\
ft_strncat.c\
ft_strncmp.c\
ft_strncpy.c\
ft_strnequ.c\
ft_strnew.c\
ft_strnstr.c\
ft_strrchr.c\
ft_strsplit.c\
ft_strstr.c\
ft_strsub.c\
ft_strtrim.c\
ft_tolower.c\
ft_toupper.c\

all: $(NAME) $(SRC) $(OBJ) $(INC)

.PHONY : all re clean fclean

$(NAME): $(OBJ_PATH) $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

$(OBJ_PATH):
	@mkdir -p $(OBJ_DIR)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(CC_FLAGS) -I $(INC_PATH) -o $@ -c $< 

clean:
	@rm -rf $(OBJ)
	@mkdir -p $(OBJ_DIR)
	@rmdir $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all
