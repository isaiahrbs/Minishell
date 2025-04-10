/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 01:26:12 by dimatayi          #+#    #+#             */
/*   Updated: 2025/03/18 04:35:45 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	malloc_error(t_data *data)
{
	data->error = MALLOC_ERROR;
	perror("");
	return (-1);
}

void	free_double_ptr(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		args[i] = NULL;
		i++;
	}
	free(args);
	args = NULL;
}

int	build_cmd(char **split_path, char *executable, char **cmd, t_data *data)
{
	int		i;
	char	*temp;

	i = -1;
	temp = NULL;
	*cmd = NULL;
	while (split_path[++i])
	{
		temp = ft_strjoin(split_path[i], "/");
		if (!temp)
			return (malloc_error(data));
		*cmd = ft_strjoin(temp, executable);
		free(temp);
		temp = NULL;
		if (!*cmd)
			return (malloc_error(data));
		if (access(*cmd, F_OK | X_OK) == 0)
			return (1);
		free(*cmd);
		*cmd = NULL;
	}
	return (0);
}

char	*get_path(char *executable, t_data *data)
{
	int		i;
	char	*cmd;
	char	**split_path;

	i = 0;
	split_path = NULL;
	while (data->envp[i])
	{
		if (ft_strncmp("PATH=", data->envp[i], 5) == 0)
		{
			split_path = real_split(data->envp[i] + 5, ':');
			if (!split_path)
			{
				perror("");
				data->error = MALLOC_ERROR;
				return (NULL);
			}
			break ;
		}
		i++;
	}
	build_cmd(split_path, executable, &cmd, data);
	free_double_ptr(split_path);
	return (cmd);
}

int	ft_exec(char *executable, char **cmd, t_data *data)
{
	char	*full_path;

	execve(executable, cmd, data->envp);
	full_path = NULL;
	full_path = get_path(executable, data);
	if (!full_path)
		return (0);
	execve(full_path, cmd, data->envp);
	perror("");
	free(full_path);
	full_path = NULL;
	return (0);
}
