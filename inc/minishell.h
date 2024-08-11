/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:54:17 by wel-safa          #+#    #+#             */
/*   Updated: 2024/08/11 17:42:09 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define READ_END 0
# define WRITE_END 1

# define CMD_ERR -1
# define PATH 0
# define BUILTIN 1
# define NO_CMD 2

# define FD_OUT 1
# define APPEND 2
# define FD_IN 3
# define HEREDOC 4

typedef struct s_state
{
	int		last_exit_status;
	char	**env;
	char	*input;
	t_list	*words;
	t_list	*cmds;
	int		num_of_processes;
	int		**pipes;
	int		*pids;
}	t_state;

typedef struct s_node
{
	t_list	*words;
	char	*cmd;
	int		cmd_flag;
	char	**args;
	char	*hd_content;
	int		append;
	int		fd_in;
	int		fd_out;
	int		err_flag;
}	t_node;

// environ.c
void	set_env(t_state *state, char **envp);
char	**copy_env(char **env, int add_flag);
void	set_env_var(t_state *shell, char *var, char* value);
char	*create_new_var(char *var, char *value);
char	*find_var_value(t_state *state, char *var);

// initialize.c
void	init_minishell(t_state *state, char **envp);

// cleanup.c
void	cleanup_shell(t_state *shell);
void	cleanup_shell_exit(t_state *state);
void	free_strarr(char **strarr);

// input_handller.c
void	input_handler(t_state *state);
int		carroting(t_state *state, int start);
int		wording(t_state *state, int start);
int		piping(t_state *state, int i);

// input_handler_utils.c
int		carrotcount(t_state *state, int start);
int		find_word_end(t_state *state, int i);
int		find_closed_quote(t_state *state, int i);
void	create_word(t_state *state, int start, int end);

// nodes.c
void	nodes(t_state *state);

// heredoc.c
void	heredoc_in(t_state * state);

// expansion.c
void	expansion(t_state *state);
void	toexpand(t_state *state, char **word);
int		expand(t_state *state, char **word, int i);
char	*strreplace(char **word, char *rep, int i, int j);
void	substr_words(char **first, char **second, char *word, int i, int j);
int		var_letter(char c);

// splitting .c
void	splitting(t_state *state);

// quotes.c
void	quotes(t_state *state);
void	removequotes(char **word);
int		find_end_quote(char *word, int i);


// delete later test functions
void	print_list(t_list *node);

#endif