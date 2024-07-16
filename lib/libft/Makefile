# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/10 10:42:56 by wel-safa          #+#    #+#              #
#    Updated: 2024/01/21 18:38:59 by wel-safa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libft.a
#SRC := $(wildcard *.c) #needs to be explicitely written
SRC	:= ft_atoi.c ft_isalnum.c ft_isdigit.c ft_memchr.c ft_memmove.c\
	ft_putendl_fd.c ft_split.c ft_striteri.c ft_strlcpy.c ft_strnstr.c\
	ft_substr.c ft_bzero.c ft_isalpha.c ft_isprint.c ft_memcmp.c\
	ft_memset.c ft_putnbr_fd.c ft_strchr.c ft_strjoin.c ft_strlen.c\
	ft_strrchr.c ft_strncmp.c ft_tolower.c ft_calloc.c ft_isascii.c ft_itoa.c\
	ft_memcpy.c ft_putchar_fd.c ft_putstr_fd.c ft_strdup.c ft_strlcat.c\
	ft_strmapi.c ft_strtrim.c  ft_toupper.c
OBJS := ${SRC:.c=.o}

BONUSSRC := ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
BONUSOBJS := ${BONUSSRC:.c=.o}

EXTRASRC := ft_printf_base.c ft_printf.c ft_printf_putnbr.c
EXTRAOBJS := $(EXTRASRC:.c=.o)

HEADER := libft.h
EXTRAHEADER := ft_printf.h

CFLAGS := -Wall -Werror -Wextra
ARFLAGS := rcs

all: $(NAME) bonus extra

#comments on creating library commands:
#1) creates object files not executables
#2) create a static library file from object files
#3) write/update an object-file index to the archive

$(NAME): $(OBJS) $(HEADER)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)
	ranlib $(NAME)

extra: $(EXTRAOBJS) $(EXTRAHEADER)
	$(AR) $(ARFLAGS) $(NAME) $(EXTRAOBJS)
	ranlib $(NAME)

bonus: $(BONUSOBJS)
	$(AR) $(ARFLAGS) $(NAME) $(BONUSOBJS)
	ranlib $(NAME)

clean:
	$(RM) -f $(OBJS) $(BONUSOBJS) $(EXTRAOBJS)

fclean: clean
	$(RM) -rf $(NAME)

re: fclean all

.PHONY: all extra bonus clean fclean re
