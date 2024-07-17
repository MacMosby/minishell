/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:10:50 by wel-safa          #+#    #+#             */
/*   Updated: 2024/07/17 19:32:21 by wel-safa         ###   ########.fr       */
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
	//char* input;
	t_state state;
	
	/********DELETE?*********/
	argc = ft_strlen(argv[0]);
	/************************/

	set_env(&state, envp);
	set_env_var(&state, "NEWVAR", "MARC");
	//print_env(state.env);
	set_env_var(&state, "NEWVAR", "LOLA");
	//print_env(state.env);
	set_env_var(&state, "NEWVAR", 0);
	//print_env(state.env);
	set_env_var(&state, "NEWVAR", "BITCH!");
	//print_env(state.env);
	
	// input = NULL;
	// input = readline("This is my prompt: ");
	// while(strlen(input))
	// {
	// 	printf("\nprinting...\n %s\n", input);
	// 	add_history(input);	
	// 	free(input);
	// 	input = NULL;
	// 	input = readline("This is my prompt: ");
	// }
	// free(input);
	// rl_clear_history();

	cleanup_shell(&state);
	return (0);
}

/*Cleans up shell on exit
1- frees the environment variables
*/
void	cleanup_shell(t_state *state)
{
	// Free state->env
	free_strarr(state->env);
}

/*frees an array of strings*/
void	free_strarr(char **strarr)
{
	int i;

	i = 0;
	while(strarr[i] != NULL)
	{
		free(strarr[i]);
		i++;
	}
	free(strarr[i]);
	free(strarr);
}
