# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ftrujill <ftrujill@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/14 15:52:13 by nvienot           #+#    #+#              #
#    Updated: 2020/01/15 18:36:48 by ftrujill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= lem-in 

prsdir	:= Sources/Parse_files
parse	:= parse.c check_error.c free_btree_n_info.c btree_fct.c
parse	+= btree_to_data.c btree_new_link.c btree_new_room.c btree_rotate.c
parse	:= $(addprefix $(prsdir)/, $(parse))

auxdir	:= Sources/Auxiliary_files
aux		:= end_free.c end_free_2.c error_msg.c initialize.c
aux		:= $(addprefix $(auxdir)/, $(aux))

algodir	:= Sources/Algorithm_files
algo	:= algorithm_0.c algorithm_1.c algorithm_2.c algorithm_3.c aux_copy.c
algo	+= print_sol.c check_sol.c aux_print.c
algo	:= $(addprefix $(algodir)/, $(algo))

SRCS	:= $(parse) $(aux) $(algo) Sources/main.c

CC		:= gcc

INC.	:= -I libft/inc/ -I Includes/

FLAGS	:=  -Wall -Werror -Wextra -O2

OBJS	:= $(SRCS:.c=.o)

LIB		:= libft/libft.a

RM		:= rm -rf

.SILENT	:

.PHONY	: all clean fclean re

#Colors
_BLACK=\x1b[30m
_RED=\x1b[31m
_GREEN=\x1b[32m
_YELLOW=\x1b[33m
_BLUE=\x1b[34m
_PURPLE=\x1b[35m
_CYAN=\x1b[36m
_WHITE=\x1b[37m
_END=\x1b[0m

all		:	$(NAME)

$(NAME)	:	$(OBJS) Makefile Includes/lemin.h
			make -C libft/
			$(CC) -o $(NAME) $(OBJS) $(LIB) $(F.WORK)
			
			echo "\n"
			echo "$(_YELLOW) _                          _             _           ____                       _        " 
			echo "$(_YELLOW)| |       ___   _ __ ___   (_)  _ __     (_)  ___    |  _ \    ___    __ _    __| |  _   _ "
			echo "$(_RED)| |      / _ \ | \'_ \` _ \ | | | '_ \    | | / __|   | |_) |  / _ \  / _\` |  / _\` | | | | |"
			echo "$(_PURPLE)| |___  |  __/ | | | | | | | | | | | |   | | \__ \   |  _ <  |  __/ | (_| | | (_| | | |_| |"
			echo "$(_CYAN)|_____|  \___| |_| |_| |_| |_| |_| |_|   |_| |___/   |_| \_\  \___|  \__,_|  \__,_|  \__, |"
			echo "$(_YELLOW)$(_RED)By $(_PURPLE)auguyon $(_BLUE)&& $(_CYAN)ftrujill $(_GREEN)2019 $(_YELLOW)!$(_WHITE)!$(_END)$(_GREEN)                                                       |___/  "
			echo "\n"

$(OBJS)	: 	%.o: %.c
			$(CC) $(FLAGS) $(INC.) -c $< -o $@

clean	:
			@$(RM) $(OBJS)
			make clean -C libft/
			echo "$(_RED)Clean ! $(_GREEN)OK$(_END)"

fclean	:	clean
			@$(RM) $(NAME)
			make fclean -C libft/
			echo "$(_RED)Fclean ! $(_GREEN)OK$(_END)"

re		:	fclean all
			make re -C libft/

acl		:	all clean
			make recl -C libft/