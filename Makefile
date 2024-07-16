# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/21 17:52:21 by wel-safa          #+#    #+#              #
#    Updated: 2024/07/14 18:19:48 by wel-safa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
#--- DIRECTORIES ---
SRCDIR := src
INCDIR := inc
OBJDIR := obj
LIBFTDIR := lib/libft
#--- LIBRARIES ---
LIBFT := $(LIBFTDIR)/libft.a
#--- SOURCES ---
SRCS := $(addprefix $(SRCDIR)/, minishell.c environ.c)
#--- OBJECTS ---
OBJS := $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
#--- HEADERS ---
HEADERS := $(addprefix $(INCDIR)/, minishell.h)
LIBFTHEADERS := $(addprefix $(LIBFTDIR)/, libft.h ft_printf.h)
#--- FLAGS ---
CC := cc
CFLAGS := -Wall -Wextra -Werror -I$(INCDIR) -I$(LIBFTDIR) -g
LDFLAGS := -L$(LIBFTDIR)
LDLIBS := -lft -lreadline

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(HEADERS) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS) $(LDLIBS)

$(LIBFT): $(LIBFTHEADERS)
	$(MAKE) -C $(LIBFTDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	$(RM) $(OBJS)
	$(RM) -r $(OBJDIR)
	$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all
