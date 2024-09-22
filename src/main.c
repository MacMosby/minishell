/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:10:50 by wel-safa          #+#    #+#             */
/*   Updated: 2024/09/22 18:33:26 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

void	exec_minishell(t_state *state)
{
	setup_heredoc_signals_main();
	if (input_handler(state) == 0)
	{
		setup_exec_signals();
		executor(state);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_state	state;

	init_minishell(&state, argc, argv, envp);
	while (1)
	{
		/* if (g_signal)
				state.exit_status = 128 + g_signal; */
		g_signal = 0;
		setup_cli_signals();
		state.input = readline("minishell:~$ ");
		if (g_signal)
			state.exit_status = 128 + g_signal;
		if (state.input == NULL)
		{
			printf("exit\n");
			break ;
		}
		add_history(state.input);
		g_signal = 0;
		exec_minishell(&state);
		cleanup_shell(&state);
	}
	cleanup_shell_exit(&state);
	return (state.exit_status);
}

/****************************************/
/*****Functions for Testing Purposes*****/
/*void	print_env(char **env)
{
	int i = 0;
	if (!env)
		return ;
	if (!(*env))
		return ;
	while(env[i])
		ft_printf("%s\n", env[i++]);
}*/
/*void	print_list(t_list *node)
{
	while(node)
	{
		printf("address: %p - ", node->content);
		printf("%s\n", (char *)(node->content));
		node = node->next;
	}
}*/
/*void	print_cmds(t_state *state)
{
	// for testing print list of commands
	t_list *cmd;
	cmd = state->cmds;
	int j = 1;
	while (cmd)
	{
		t_node * node;
		node = (t_node *) cmd->content;
		printf("CMD %i:\n", j);
		printf("\nword list:\n");
		print_list(node->words);
		printf("\ncmd and cmd flag:\n");
		ft_printf("%s\n", node->cmd);
		printf("%i", node->cmd_flag);
		printf("\nargs:\n");
		print_env(node->args);
		printf("\nfd_in: %i\n", node->fd_in);
		printf("fd_out: %i\n", node->fd_out);
		ft_printf("hd_content: %s\n", node->hd_content);
		printf("err_flag: %i\n", node->err_flag);
		j++;
		cmd = cmd->next;
	}
}*/
/****************************************/

/* void	sig_cli(t_state *state)
{
	//printf("\n");
	//rl_on_new_line();
	//rl_replace_line("", 0);
	//rl_redisplay();
	printf("WE GET HERE IF WE GET SIGINT ON THE COMMAND LINE\n");
	state->exit_status = 130;
	g_signal = 0;
} */

/* void	sig_hd(t_state *state)
{
	printf("WE GET HERE IF WE GET SIGINT IN THE HEREDOC OR ON THE COMMAND LINE\n");
	state->exit_status = 130;
	g_signal = 0;
} */

/* void	sig_exec(t_state *state)
{
	printf("WE GET HERE IF WE GET SIGINT DURING EXECUTION");
	state->exit_status = 130;
	//printf("exit status: %d\n", state->exit_status);
	g_signal = 0;
} */
