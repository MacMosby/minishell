/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:53:07 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/08/21 21:53:47 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_state *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		printf("%s\n", data->env[i]);
		i++;
	}
}

char	**copy_env_unset(char **env)
{
	int		count;
	char	**env_copy;
	int 	i;
	int		j;

	count = 0;
	i = 0;
	j = 0;
	while (env[count] != NULL)
		count++;
	count++;
	while (env[count] != NULL)
		count++;
	env_copy = (char **)malloc((count + 1 - 1) * sizeof(char *));
	while (i < count)
	{
		if (env[i])
			env_copy[i + j] = ft_strdup(env[i]);
		else
			j -= 1;
		i++;
	}
	env_copy[count - 1] = NULL;
	return env_copy;
}

void	ft_unset(t_state *data, char *var)
{
	//size_t	len;
	int	i;
	int	j;
	char**	new_env;

	//len = ft_strlen(var);
	i = 0;
	while (data->env[i])
	{
		j = 0;
		while (data->env[i][j])
		{
			if (data->env[i][j] == '=')
			{
				if ((ft_strncmp(ft_substr(data->env[i], 0, j), var, j) == 0)
					&& (var[j] == 0))
				{
					printf("DO WE GET HERE ??? \n");
					free(data->env[i]);
					data->env[i] = NULL;
					new_env = copy_env_unset(data->env);
					//free_strarr(data->env);
					data->env = new_env;
					return;
				}
				else
					break;
			}
			j++;
		}
		i++;
	}
}

// needs to work without arguments
void	ft_export(t_state *data, char *str)
{
	int	i;
	char	*var;
	char	*value;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			var = ft_substr(str, 0, i);
			value = ft_substr(str, i + 1, ft_strlen(str) - i);
			set_env_var(data, var, value);
			return;
		}
		i++;
	}
}

// needs to work with arguments ???
void	ft_exit(void)
{
	rl_clear_history();
	// EXIT HANDLE
	exit (0);
}

/* checks if the input string is the -n flag for echo to not print \n */
int	flag_check(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (str[0] == '-')
	{
		i = 1;
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		if (i > 1)
			return (1);
	}
	return (0);
}

/* takes an array of strings an and prints them without the first one */
void	ft_echo(char **arr)
{
	int	i;
	int	flag = 0;
	int first = 1;

	i = 1;
	while (arr[i] && flag_check(arr[i]))
	{
		flag = 1;
		i++;
	}
	while (arr[i])
	{
		if (first)
		{
			printf("%s", arr[i]);
			first = 0;
		}
		else
			printf(" %s", arr[i]);
		i++;
	}
	if (!flag)
		printf("%s\n", "");
	// EXIT HANDLE
	exit(0);
}

/* prints the current working directory */
void	ft_pwd(void)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	// EXIT HANDLE
	exit(0);
}

/* takes an input string and changes the current working directory to the path given as string */
void	ft_cd(char *str)
{
	int errno;

	if (chdir(str) == -1)
	{
		if (errno == 2)
			printf("minishell: cd: %s: No such file or directoy\n", str);
	}
	// EXIT HANDLE
	exit(0);
}

/* routes to the needed builtin function and calls it */
// void	invoke_builtin(t_state *data, t_node *curr)
void	invoke_builtin(t_state *data, t_node *curr)
{
	if (ft_strncmp(curr->cmd, "echo", 4) == 0)
	{
		// call echo and pass curr
		ft_echo(curr->args);
		printf("Hello from echo\n");
	}
	else if (ft_strncmp(curr->cmd, "cd", 2) == 0)
	{
		// call cd and pass curr
		printf("Hello from cd\n");
		ft_cd(curr->args[1]);
	}
	else if (ft_strncmp(curr->cmd, "pwd", 3) == 0)
	{
		// call pwd and pass curr
		printf("Hello from pwd\n");
		ft_pwd();
	}
	else if (ft_strncmp(curr->cmd, "export", 6) == 0)
		// call export and pass curr
		printf("Hello from export\n");
	else if (ft_strncmp(curr->cmd, "unset", 5) == 0)
		// call unset and pass curr
		printf("Hello from unset\n");
	else if (ft_strncmp(curr->cmd, "env", 3) == 0)
		// call env and pass data struct ???
		printf("Hello from env\n");
	else if (ft_strncmp(curr->cmd, "exit", 4) == 0)
	{
		// call exit and pass data struct ???
		printf("Hello from exit and something: %d\n", data->exit_status);
		ft_exit();
	}
}
