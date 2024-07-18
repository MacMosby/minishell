/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:54:17 by wel-safa          #+#    #+#             */
/*   Updated: 2024/07/18 22:10:59 by wel-safa         ###   ########.fr       */
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

int g_signal;

typedef struct s_state
{
	int		last_exit_status;
	char	**env;
	char	*input;
	char	*seperators;
	t_list	*cmds;
	int		num_of_processes;
	int		**pipes;
	int		*pids;
}	t_state;

typedef struct s_list
{
	void	*content;
	struct s_list	*next;
}	t_list;

typedef struct s_node
{
	char	*cmd;
	int		cmd_flag;
	char	*args;
	char	*infile;
	char	*outfile;
	int		append;
	int		fd_in;
	int		fd_out;
}	t_node;

// environ.c
void	set_env(t_state *state, char **envp);
char	**copy_env(char **env, int add_flag);
void	set_env_var(t_state *shell, char *var, char* value);
char	*create_new_var(char *var, char *value);

// cleanup.c
void	cleanup_shell(t_state *shell);
void	free_strarr(char **strarr);

#endif