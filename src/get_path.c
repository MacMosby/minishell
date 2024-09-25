/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 22:59:21 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/09/25 19:11:23 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* frees split memory allocs */
void	ft_free_splits(char **splits)
{
	size_t	i;

	i = 0;
	while (splits[i])
		free(splits[i++]);
	free(splits[i]);
	free(splits);
}

char	*ft_get_env_path(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (env[i]);
	}
	return (NULL);
}

char	*ft_get_exec_path(t_state *state, char **path_split, char *cmd)
{
	int		i;
	char	*path;
	size_t	path_size;

	i = -1;
	while (path_split[++i])
	{
		path_size = ft_strlen(path_split[i]) + ft_strlen(cmd) + 2;
		path = (char *)ft_calloc(sizeof(char), path_size);
		if (!path)
			error_exit(state);
		ft_strlcat(path, path_split[i], path_size);
		ft_strlcat(path, "/", path_size);
		ft_strlcat(path, cmd, path_size);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
	}
	return (NULL);
}

/*void ft_printstr(char **str)
{
	int i = 0;
	// I think I have a similar function
	// should maybe delete one of them
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
}*/

char	*get_path(t_state *data, char *cmd)
{
	char	*env_path;
	char	**path_split;
	char	*exec_path;

	if (ft_strlen(cmd) == 0)
	{
		write(2, " Command not found\n", 19);
		return (NULL);
	}
	env_path = ft_get_env_path(data->env);
	if (!env_path)
	{
		write(2, " No such file or directory\n", 27);
		return (NULL);
	}
	path_split = ft_split(env_path + 5, ':');
	exec_path = ft_get_exec_path(data, path_split, cmd);
	ft_free_splits(path_split);
	if (exec_path)
		return (exec_path);
	free(exec_path);
	write(2, " command not found\n", 19);
	return (NULL);
}
