/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:54:17 by wel-safa          #+#    #+#             */
/*   Updated: 2024/09/22 19:21:54 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* valgrind -s --suppressions=readline.supp --leak-check=full
--show-leak-kinds=all ./minishell */

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
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>

# define READ_END 0
# define WRITE_END 1

# define CMD_OK 0

# define PATH 2
# define BUILTIN 1
# define NO_CMD 0

# define FD_OUT 1
# define APPEND 2
# define FD_IN 3
# define HEREDOC 4

typedef struct s_state
{
	int		exit_status;
	char	**env;
	char	*input;
	t_list	*words;
	t_list	*cmds;
	int		num_of_processes;
	int		**pipes;
	int		*pids;
	char	*builtins[8];
}	t_state;

typedef struct s_node
{
	t_list	*words;
	char	*cmd;
	int		cmd_flag;
	char	**args;
	char	*hd_content;
	int		hd_expand_flag;
	int		fd_in;
	int		fd_out;
	int		err_flag;
}	t_node;

extern int	g_signal;

// environ.c
void	set_env(t_state *state, char **envp);
char	**copy_env(t_state *state, char **env, int add_flag);
void	set_env_var(t_state *shell, char *var, char *value, int equal);
char	*create_new_var(t_state *state, char *var, char *value);
char	*find_var_value(t_state *state, char *var);

// initialize.c
void	init_minishell(t_state *state, int ac, char **av, char **envp);
void	init_pipes(t_state *data, int i);
void	init_pids(t_state *data);

// cleanup.c
void	cleanup_shell(t_state *shell);
void	cleanup_shell_exit(t_state *state);
void	free_nodes(void *node);
void	free_strarr(char **strarr);
void	error_exit(t_state *state);

// input_handller.c
int		input_handler(t_state *state);
int		parsing(t_state *state, int i);
int		wording(t_state *state, int start);
int		piping(t_state *state, int i);

// input_carrots.c
int		carroting(t_state *state, int start);
int	carroting_errors(t_state *state, char c, int start);


// input_handler_utils.c
int		carrotcount(t_state *state, int start);
int		find_word_end(t_state *state, int i);
int		find_closed_quote(t_state *state, int i);
void	create_word(t_state *state, int start, int end);

// nodes.c
void	nodes(t_state *state);

// heredoc.c
void	heredoc_in(t_state *state);
void	get_heredoc_input(t_state *state, t_node *cmd_content, t_list *words);
char	*ft_here_doc(t_state *state, t_list *word);
void	heredoc_expansions(t_state *state, char **hd_content);

// heredoc_utils.c
char	*ft_join_free(t_state *state, char *s1, char *s2, size_t i);

// expansion.c
void	expansion(t_state *state);
void	toexpand(t_state *state, char **word);
int		expand(t_state *state, char **word, int i, int hd_flag);
char	*strreplace(char **word, char *rep, int i, int j);
void	substr_words(char **first, char **second, char *word, int i, int j);
int		var_letter(char c);
void	delete_empty_words(t_list *cmd);

// splitting .c
void	splitting(t_state *state);

// quotes.c
void	quotes(t_state *state);
void	removequotes(char **word);
int		find_end_quote(char *word, int i);

// redirections.c
void	redirections(t_state *state);
void	cmd_redirections(t_state *state, t_list *cmd);
int		set_fds(t_state *state, t_node *cmd_node, int carrots, char **filename);
int		found_carrot(char *str);

// redirections_utils.c
int		filename_expansion_error(char **filename);
int		filename_cut_spaces(char **filename);
int		set_fd_out(t_node *curr, char *file, int append);
int		set_fd_in(t_state *state, t_node *curr, char *file);

// list_manipulation.c
void	wordlist_to_cmdarr(t_state *state, t_node *cmd);
void	delete_redirections(t_list **words);

// handle_cmd.c
void	cmd_loop(t_state *state);
void	handle_cmd(t_state *data, t_node *curr, char *str);
int		check_for_dir(char *str);
int		check_for_builtin(char *cmd, char **builtins);

// get_path.c
char	*get_path(t_state *data, char *cmd);
char	*ft_get_exec_path(t_state *state, char **path_split, char *cmd);
char	*ft_get_env_path(char **env);
void	ft_free_splits(char **splits);

// executor.c
void	executor(t_state *data);
void	execution_loop(t_state *data);
void	fork_executor(t_state *data, t_node *curr, int i);

// executor_utils.c
void	redirect_to_pipes(t_state *data, int i);
void	redirect_in_out(t_state *data, t_node *curr, int i);
void	wait_loop(t_state *data);

// executor_pipes.c
void	free_pipes(t_state *data);
void	close_pipes(t_state *data);

// builtins.c
int		invoke_builtin(t_state *data, t_node *curr);

// ft_cd.c
int		ft_cd(t_state *state, t_node *curr);

// ft_echo.c
int		flag_check(char *str, int *flag);
int		ft_echo(char **arr);

// ft_env.c
int		ft_env(t_state *data);

// ft_exit.c
int		ft_exit(t_state *data, t_node *curr);

// ft_export.c
int		do_export(t_state *data, char *s);
int		ft_export(t_state *data, t_node *curr);

// ft_pwd.c
int		ft_pwd(void);

// ft_unset.c
char	**copy_env_unset(t_state *state, char **env);
int		ft_unset(t_state *data, t_node *curr);

// signals_cli.c
void	setup_cli_signals(void);

// signals_exec.c
void	setup_exec_signals(void);

// signals_heredoc.c
void	setup_heredoc_signals_main(void);
void	setup_heredoc_signals_child(void);

// delete later test functions
void	print_list(t_list *node);
void	print_cmds(t_state *state);

#endif
