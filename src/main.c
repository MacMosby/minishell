/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:10:50 by wel-safa          #+#    #+#             */
/*   Updated: 2024/08/12 20:06:19 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/****************************************/
/*****Functions for Testing Purposes*****/
void	print_env(char **env)
{
	int i = 0;
	while(env[i])
		printf("%s\n", env[i++]);
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


int	main(int argc, char **argv, char **envp)
{
	t_state state;
	
	/********DELETE?*********/
	argc = ft_strlen(argv[0]);
	argc++;
	/************************/

	init_minishell(&state, envp);
	// set_env_var(&state, "ARG", "echo -ls");
	while (1)
	{
		state.input = readline("minishell:~$ "); // display prompt
		if (state.input == NULL)
			// Ctl-D (EOF) handle
			break;
		add_history(state.input);
		input_handler(&state);
		
		// for testing purposes
		// printf("SUCCESS!!\n");
		// print_list(state.words);
		
		cleanup_shell(&state);
	}
	cleanup_shell_exit(&state);
	return (0);
}
