/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:53:07 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/08/21 22:41:01 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_state *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		printf("%s\n", data->env[i]);
		i++;
	}
	return (0);
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

int	ft_unset(t_state *data, t_node *curr)
{
	//size_t	len;
	int	i;
	int	j;
	char**	new_env;

	//len = ft_strlen(var);
	if (!curr->args[1])
		return (0);
	i = 0;
	while (data->env[i])
	{
		j = 0;
		while (data->env[i][j])
		{
			if (data->env[i][j] == '=')
			{
				if ((ft_strncmp(ft_substr(data->env[i], 0, j), curr->args[1], j) == 0)
					&& (curr->args[1][j] == 0))
				{
					free(data->env[i]);
					data->env[i] = NULL;
					new_env = copy_env_unset(data->env);
					//free_strarr(data->env);
					data->env = new_env;
					return (0);
				}
				else
					break;
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	do_export(t_state *data, char *s)
{
	int		i;
	char	*var;
	char	*value;

	i = 0;
	if (!ft_isalpha(s[i]))
		return (1);
	i++;
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '=')
			return (1);
		if (s[i] == '=')
		{
			var = ft_substr(s, 0, i);
			value = ft_substr(s, i + 1, ft_strlen(s) - i);
			set_env_var(data, var, value);
			return (0);
		}
		i++;
	}
	// if no '=' is found
	return (0);
}

// needs to work without arguments and with more than one
int	ft_export(t_state *data, t_node *curr)
{
	int	i;
	int	ret;
	int	tmp;

	ret = 0;
	tmp = 0;
	i = 1;
	while (curr->args[i])
	{
		ret = do_export(data, curr->args[i]);
		i++;
	}
	if (ret)
		write(2, " not a valid identifier\n", 24);
	return (ret);
}

int	ft_is_num(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

// needs to work with arguments ???
void	ft_exit(t_state *data, t_node *curr)
{
	printf("exit\n");
	if (curr->args[1] && !curr->args[2])
	{
		if (ft_is_num(curr->args[1]))
			exit(ft_atoi(curr->args[1]));
		write(2, " numeric argument required\n", 27);
		// EXIT HANDLE
		// MARC START
		cleanup_shell_exit(data);
		// MARC END
		exit (2);
	}
	else if (curr->args[1] && curr->args[2])
	{
		write(2, " too many arguments\n", 20);
		// EXIT HANDLE
		// MARC START
		cleanup_shell_exit(data);
		// MARC END
		exit (1);
	}
	// EXIT HANDLE
	// MARC START
	cleanup_shell_exit(data);
	// MARC END
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
int	ft_echo(char **arr)
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
	return (0);
}

/* prints the current working directory */
int	ft_pwd(void)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	return (0);
}

/* takes an input string and changes the current working directory to the path given as string */
int	ft_cd(t_node *curr)
{
	int errno;
	if (curr->args[1] && !curr->args[2])
	{
		if (chdir(curr->args[1]) == -1)
		{
			if (errno == 2)
				perror(" ");
			return (1);
		}
	}
	else if (curr->args[1] && curr->args[2])
	{
		write(2, " too many arguments\n", 20);
		return (1);
	}
	return (0);
}

/* routes to the needed builtin function and calls it */
int	invoke_builtin(t_state *data, t_node *curr)
{
	if (ft_strncmp(curr->cmd, "echo", 4) == 0)
	{
		return(ft_echo(curr->args));
	}
	else if (ft_strncmp(curr->cmd, "cd", 2) == 0)
	{
		return(ft_cd(curr));
	}
	else if (ft_strncmp(curr->cmd, "pwd", 3) == 0)
	{
		return(ft_pwd());
	}
	else if (ft_strncmp(curr->cmd, "export", 6) == 0)
		return(ft_export(data, curr));
	else if (ft_strncmp(curr->cmd, "unset", 5) == 0)
		return(ft_unset(data, curr));
	else if (ft_strncmp(curr->cmd, "env", 3) == 0)
		ft_env(data);
	else if (ft_strncmp(curr->cmd, "exit", 4) == 0)
	{
		// call exit and pass data struct ???
		ft_exit(data, curr);
	}
	// what should be the return value ?
	return(1);
}
