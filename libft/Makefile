# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/17 17:43:49 by auguyon           #+#    #+#              #
#    Updated: 2019/12/09 18:32:33 by auguyon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL			:= /bin/sh
.SUFFIXES		:=
.SUFFIXES		:= .c .o
.DEFAULT_GOAL	:= all
DEBUG			:= 0

CC				:= gcc

ifeq ($(DEBUG), 0)
	CFLAGS		:= -Wall -Wextra -Werror -O2
else
    CFLAGS		:= -Wall -Wextra -Werror -g3 -O0 -fsanitize=address
endif

CFLAGS			+= -I ./inc

NAME			:= libft.a

VPATH			:= src

prtdir	:= print
prt		:= ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c
prt		+= ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c
prt		+= ft_putnstr.c
prt		:= $(addprefix $(prtdir)/, $(prt))

listdir	:= list
list	:= ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstnew.c ft_lstiter.c 
list	+= ft_lstmap.c 
list	:= $(addprefix $(listdir)/, $(list))

memdir	:= mem
mem		:= ft_bzero.c ft_memalloc.c ft_memccpy.c ft_memchr.c 
mem		+= ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c 
mem		+= ft_memlcat.c ft_memlcpy.c 
mem		:= $(addprefix $(memdir)/, $(mem))

strdir	:= str
str		:= ft_strtrim.c ft_strsplit.c ft_strnew.c ft_strncmp.c ft_strmapi.c
str		+= ft_strjoin.c ft_strdup.c ft_strcmp.c ft_strcchr.c ft_strdel.c
str		+= ft_strsub.c ft_strrchr.c ft_strnequ.c ft_strnccmp.c ft_strmap.c
str		+= ft_strstr.c ft_strnstr.c ft_strndup.c ft_strncat.c  ft_strlen.c
str		+= ft_strspn.c ft_strnjoin.c ft_strncpy.c ft_strmultidel.c ft_strlcat.c
str 	+= ft_striteri.c ft_strclr.c ft_strcat.c ft_striter.c ft_strcspn.c
str		+= ft_strequ.c ft_strcpy.c ft_strccmp.c ft_strchr.c ft_strjoin_free.c
str		+= ft_strclen.c ft_strcdup.c ft_strrev.c ft_strlower.c ft_isint.c
str		:= $(addprefix $(strdir)/, $(str))

toadir	:= toa
toa 	:= ft_itoa.c ft_lltoa.c ft_stoa_base.c ft_ulltoa_base_caps.c ft_ctoa.c
toa 	+= ft_ustoa_base_caps.c ft_utoa_base_caps.c ft_ztoa_base_caps.c
toa 	+= ft_itoa_base.c ft_lltoa_base.c ft_ulltoa.c ft_ustoa.c ft_utoa.c
toa 	+= ft_itoa_base_caps.c ft_stoa.c ft_ulltoa_base.c ft_ustoa_base.c
toa 	+= ft_ztoa.c ft_utoa_base.c ft_ztoa_base.c ft_stoa_base_caps.c
toa 	+= ft_dtoa.c ft_ldtoa.c ft_ldtoa_concat.c ft_uctoa_base.c ft_uctoa.c
toa		+= ft_uctoa_base_caps.c
toa		:= $(addprefix $(toadir)/, $(toa))

utildir	:= utility
util	:= ft_atoi.c ft_atoi_base.c ft_isdigit.c ft_min.c ft_max.c ft_abs.c
util	+= ft_count_c.c ft_fill_nb.c ft_malloc_error.c ft_utoi.c ft_atoll.c
util	:= $(addprefix $(utildir)/, $(util))

gnldir	:= Get_Next_Line
gnl		:= get_next_line.c
gnl		:= $(addprefix $(gnldir)/, $(gnl))

prfdir	:= ft_printf
prf		:= aux.c aux_print.c conversions_1.c conversions_2.c conversions_3.c
prf		+= ft_printf.c get_arg.c
prf		:= $(addprefix $(prfdir)/, $(prf))

objdir	:= obj
ddir	:= dep
src		:= $(ctrl) $(prt) $(toa) $(list) $(util) $(mem) $(str) $(gnl) $(prf)
obj		:= $(addprefix $(objdir)/, $(src:%.c=%.o))
dep		:= $(addprefix $(ddir)/, $(src:%.c=%.d))

-include $(dep)

%/.f:
	mkdir -p $(@D)
	touch $@

.PRECIOUS: %/.f
.SECONDEXPANSION:
.PRECIOUS: $(obj)
.SILENT:

dname = $(subst $(1),$(2),$(basename $(3))).d
$(objdir)/%.o:	%.c $$(@D)/.f $$(subst $(objdir),$(ddir),$$(@D))/.f
	$(CC) $(CFLAGS) -c $< -o $@ -MMD -MP -MF $(call dname,$(objdir),$(ddir),$@)

.PHONY: all
all: $(NAME)

ARFLAGS	:=	urcs
.NOTPARALLEL: $(NAME)
$(NAME): 	$$@($(obj))

.PHONY: clean
clean:
	$(RM) -r $(objdir) $(ddir)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
.NOTPARALLEL: re
re: fclean all
