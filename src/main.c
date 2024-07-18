/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:10:50 by wel-safa          #+#    #+#             */
/*   Updated: 2024/07/18 22:22:06 by wel-safa         ###   ########.fr       */
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
/****************************************/


int	main(int argc, char **argv, char **envp)
{
	t_state state;
	
	/********DELETE?*********/
	argc = ft_strlen(argv[0]);
	/************************/


	init_minishell(&state, envp);
	while (1)
	{
		// display prompt
		state.input = readline("minishell:~$ ");
		if (state.input == NULL)
			// Ctl-D (EOF) handle
			break;
		add_history(state.input);
		input_handler(&state);
		// executor
		free(state.input);
	}

	cleanup_shell(&state);
	return (0);
}
