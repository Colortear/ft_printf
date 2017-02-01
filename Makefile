# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkunduru <hkunduru@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/16 17:55:20 by hkunduru          #+#    #+#              #
#    Updated: 2017/01/09 23:34:20 by wdebs            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=		libftprintf.a
CC		=		gcc
CFLAGS	=		-Wall -Wextra -Werror -Wno-varargs

SRCS	=		casts.c \
				char_conv.c \
				flagsnwidth.c \
				ft_printf.c \
				int_conv.c \
				int_to_str.c \
				p_conv.c \
				print_funcs.c \
				set_options.c \
				string_conv.c

SRCS_LIB= 		ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
				ft_isblank.c ft_isdigit.c ft_islower.c ft_isprint.c \
				ft_itoa.c ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c \
				ft_isupper.c ft_lstmap.c ft_lstnew.c ft_memalloc.c \
				ft_memcpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c \
				ft_memmove.c ft_memset.c ft_putchar.c ft_putchar_fd.c \
				ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c \
				ft_putstr.c ft_putstr_fd.c ft_strcat.c ft_strchr.c ft_strclr.c \
				ft_strcmp.c ft_strcpy.c ft_strcspn.c ft_strdel.c ft_strdup.c \
				ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
				ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncmp.c \
				ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c \
				ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c ft_swap.c \
				ft_tolower.c ft_toupper.c 

HDIR		=	./includes/
LDIR		=	./libft/
SRCSDIR		=	./srcs/

OBJS			=	$(subst .c,.o,$(SRCS))
OBJS_LIB		=	$(subst .c,.o,$(SRCS_LIB))
LIST_OBJ		=	$(addprefix $(SRCSDIR), $(OBJS))
LIST_OBJ_LIB	=	$(addprefix $(LDIR), $(OBJS_LIB))

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(HDIR) -I./ -c -o $@ $<

$(NAME): $(LIST_OBJ) $(LIST_OBJ_LIB)
	ar rc $(NAME) $(LIST_OBJ) $(LIST_OBJ_LIB)
	ranlib $(NAME)

clean:
	rm -rf $(LIST_OBJ) $(LIST_OBJ_LIB)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
