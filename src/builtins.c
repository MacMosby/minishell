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
	int	j;

	i = 0;
	while (data->env[i])
	{
		j = 0;
		while (data->env[i][j])
		{
			if (data->env[i][j] == '=')
			{
				printf("%s\n", data->env[i]);
				break;
			}
			j++;
		}
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

int	do_unset(t_state *data, char *s)
{
	int	i;
	int	j;
	char**	new_env;

	i = 0;
	while (data->env[i])
	{
		j = 0;
		while (data->env[i][j])
		{
			if (data->env[i][j] == '=')
			{
				if ((ft_strncmp(ft_substr(data->env[i], 0, j), s, j) == 0)
					&& (s[j] == 0))
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

int	ft_unset(t_state *data, t_node *curr)
{
	int	i;

	i = 1;
	while (curr->args[i])
	{
		do_unset(data, curr->args[i]);
		i++;
	}
	return (0);
}

int	do_export(t_state *data, char *s)
{
	int		i;
	char	*key;
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
			key = ft_substr(s, 0, i);
			value = ft_substr(s, i + 1, ft_strlen(s) - i);
			set_env_var(data, key, value, 1);
			return (0);
		}
		i++;
	}
	key = ft_substr(s, 0, i);
	set_env_var(data, key, NULL, 0);
	// if no '=' is found
	return (0);
}

void	print_export_line(char *s)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	value = NULL;
	while (s[i])
	{
		if (s[i] == '=')
		{
			value = ft_substr(s, i + 1, ft_strlen(s) - i);
			break;
		}
		i++;
	}
	key = ft_substr(s, 0, i);
	printf("declare -x %s", key);
	if (value)
	{
		printf("=\"%s\"", value);
	}
	printf("\n");
}

int	ft_max_len(char *s1, char *s2)
{
	int len1;
	int	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 > len2)
		return (len1);
	return (len2);
}

void	print_export_list(char **env)
{
	int		i;
	int		j;
	int		len;
	char	*last;
	char	*min;

	last = NULL;
	if (!env || !(*env))
		return ;
	min = env[0];
	j = 0;
	len = 0;
	while (env[len])
		len++;
	while (j < len)
	{
		if (last)
			min = NULL;
		i = 0;
		while (env[i])
		{
			if (!last)
			{
				if (ft_strncmp(min, env[i], ft_max_len(min, env[i])) > 0)
					min = env[i];
			}
			else
			{
				if (ft_strncmp(env[i], last, ft_max_len(env[i], last)) > 0)
				{
					if (!min)
						min = env[i];
					else
					{
						if (ft_strncmp(min, env[i], ft_max_len(min, env[i])) > 0)
							min = env[i];
					}
				}
			}
			i++;
		}
		if (last && min)
		{
			if (!ft_strncmp(min, last, ft_max_len(min, last)))
				return ;
		}
		print_export_line(min);
		last = min;
		j++;
	}
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
	if (!curr->args[i])
	{
		print_export_list(data->env);
		return (0);
	}
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
