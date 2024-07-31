/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:10:50 by wel-safa          #+#    #+#             */
/*   Updated: 2024/07/31 23:00:52 by wel-safa         ###   ########.fr       */
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
	set_env_var(&state, "ARG", " echo -ls");
	//print_env(state.env);
	while (1)
	{
		// display prompt
		state.input = readline("minishell:~$ ");
		if (state.input == NULL)
			// Ctl-D (EOF) handle
			break;
		add_history(state.input);
		input_handler(&state);
		printf("\nSUCCESS!!\n\n");
		print_list(state.words);
		// executor
		free(state.input);
		ft_lstclear(&(state.words), free);
	}
	cleanup_shell(&state);
	return (0);
}
