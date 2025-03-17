/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 01:26:12 by dimatayi          #+#    #+#             */
/*   Updated: 2025/03/16 01:26:32 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

int	build_cmd(char **split_path, char *executable, char **cmd)
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
			return (-1);
		*cmd = ft_strjoin(temp, executable);
		free(temp);
		temp = NULL;
		if (!*cmd)
			return (-1);
		if (access(*cmd, F_OK | X_OK) == 0)
			return (1);
		free(*cmd);
		*cmd = NULL;
	}
	return (0);
}

char	*get_path(char *executable, char **envp)
{
	int		i;
	char	*cmd;
	char	**split_path;

	i = 0;
	split_path = NULL;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
		{
			split_path = real_split(envp[i] + 5, ':');
			if (!split_path)
				perror("");
			break ;
		}
		i++;
	}
	if (!split_path)
		return (NULL);
	if (build_cmd(split_path, executable, &cmd) == -1)
		perror("");
	free_double_ptr(split_path);
	if (cmd == NULL)
		printf("command not found\n");
	return (cmd);
}

int	ft_exec(char *executable, char **cmd, char **envp)
{
	char	*full_path;

	execve(executable, cmd, envp);
	full_path = NULL;
	full_path = get_path(executable, envp);
	if (!full_path)
		return (0);
	execve(full_path, cmd, envp);
	perror("");
	free(full_path);
	full_path = NULL;
	return (0);
}
