/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:54:17 by wel-safa          #+#    #+#             */
/*   Updated: 2024/07/16 19:33:21 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include "libft.h"

typedef struct {
	int		last_exit_status;
	char	**env;
	// 
} shellstate;

// environ.c
void	set_env(shellstate *state, char **envp);
char	**copy_env(char **env, int add_flag);
void	set_env_var(shellstate *shell, char *var, char* value);
char	*create_new_var(char *var, char *value);

// main.c
void	cleanup_shell(shellstate *shell);
void	free_strarr(char **strarr);

#endif