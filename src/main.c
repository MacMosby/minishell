/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:10:50 by wel-safa          #+#    #+#             */
/*   Updated: 2024/09/12 19:51:08 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/****************************************/
/*****Functions for Testing Purposes*****/
void	print_env(char **env)
{
	int i = 0;
	if (!env)
		return ;
	if (!(*env))
		return ;
	while(env[i])
		ft_printf("%s\n", env[i++]);
}

void	print_list(t_list *node)
{
	while(node)
	{
		printf("address: %p - ", node->content);
		printf("%s\n", (char *)(node->content));
		node = node->next;
	}
}
/****************************************/

// MARC START
int	g_signal = 0;

void	sig_cli(t_state *state)
{
	/* printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay(); */
	printf("WE GET HERE IF WE GET SIGINT ON THE COMMAND LINE\n");
	state->exit_status = 130;
	g_signal = 0;
}

void	sig_hd(t_state *state)
{
	printf("WE GET HERE IF WE GET SIGINT IN THE HEREDOC OR ON THE COMMAND LINE\n");
	state->exit_status = 130;
	g_signal = 0;
}

void	sig_exec(t_state *state)
{
	printf("WE GET HERE IF WE GET SIGINT DURING EXECUTION");
	state->exit_status = 130;
	//printf("exit status: %d\n", state->exit_status);
	g_signal = 0;
}
// MARC END

int	main(int argc, char **argv, char **envp)
{
	t_state state;

	/********DELETE?*********/
	argc = ft_strlen(argv[0]);
	argc++;
	/************************/

	// MARC START
	g_signal = 0;
	// MARC END
	init_minishell(&state, envp);
	while (1)
	{
		// MARC START
		setup_cli_signals();
		// MARC END
		/* printf("TEST\n\n\n");
		print_cmds(&state);
		printf("TEST\n\n\n"); */
		state.input = readline("minishell:~$ "); // display prompt
		if (state.input == NULL)
			// Ctl-D (EOF) handle
			break;
		add_history(state.input);
		// MARC START
		//setup_heredoc_signals();
		// MARC END
		if (input_handler(&state) == 0)
		{
			// MARC START
			setup_exec_signals();
			// MARC END
			//print_cmds(&state);
			executor(&state);
			// for testing purposes
			// printf("SUCCESS!!\n");
			//print_list(state.words);
		}
		cleanup_shell(&state);
	}
	cleanup_shell_exit(&state);
	return (0);
}
