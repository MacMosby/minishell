# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/21 17:52:21 by wel-safa          #+#    #+#              #
#    Updated: 2024/09/22 23:35:59 by wel-safa         ###   ########.fr        #
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
SRCS := $(addprefix $(SRCDIR)/, main.c environ.c initialize.c cleanup.c \
input_handler.c input_handler_utils.c expansion.c splitting.c quotes.c nodes.c \
heredoc.c redirections.c redirections_utils.c list_manipulation.c get_path.c \
handle_cmd.c executor.c executor_utils.c builtins.c signals_cli.c \
signals_exec.c signals_heredoc.c ft_cd.c ft_echo.c ft_env.c ft_exit.c \
ft_export.c ft_pwd.c ft_unset.c heredoc_utils.c executor_pipes.c \
input_carrots.c expansion_utils.c ft_export_utils.c environ_manipulation.c \
minishell_utils.c)
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
