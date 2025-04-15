/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:57:27 by dimatayi          #+#    #+#             */
/*   Updated: 2025/04/15 19:48:27 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_executable(char **executable, char ***cmd, t_data *data)
{
	if (!strcmp("env", *executable))
	{
		ft_env(data, executable, cmd);
		exit(0);
	}
	if (!strcmp("export", *executable))
	{
		ft_export(data, executable, cmd);
		exit(0);
	}
	if (!strcmp("echo", *executable))
	{
		ft_echo(executable, cmd);
		exit(0);
	}
	if (!ft_exec(*executable, *cmd, data))
		ft_free(executable, cmd);
	if (data->error == MALLOC_ERROR)
		exit(1);
	write(2, "command not found\n", 18);
	//printf("command not found\n");
	exit(127);
}

int	child(t_cmd *tmp, int *prev_pipe_read, int *fd, t_data *data)
{
	char	**cmd;
	char	*executable;
	int		infile;
	int		outfile;

	init_var(&cmd, &executable, &infile, &outfile);
	while (tmp && tmp->value && tmp->type != PIPE)
	{
		if (tmp->type == HERE_DOC && here_doc(&tmp, &infile, data))
			continue ;
		is_cmd(tmp, &executable, &cmd);
		if (is_redirection(tmp, &executable, &cmd))
		{
			redirout_append(tmp, &outfile, &executable, &cmd);
			redir_in(tmp, &infile, &executable, &cmd);
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	edit_pipe_fd(infile, outfile, prev_pipe_read, fd);
	if (executable)
		ft_executable(&executable, &cmd, data);
	return (1);
}

t_cmd	*parent(int *prev_pipe_read, int *fd, t_cmd *tmp, t_data *data)
{
	pid_t	wait_result;
	int		status;

	if (*prev_pipe_read != -1)
		close(*prev_pipe_read);
	if (fd[1] != -1)
		close(fd[1]);
	*prev_pipe_read = fd[0];
	while (tmp && tmp->value && tmp-> type != PIPE)
		tmp = tmp->next;
	if (tmp && tmp->type == PIPE)
		tmp = tmp->next;
	wait_result = wait(&status);
	if (wait_result > 0)
	{
		if (WIFEXITED(status))
			data->exit_code = WEXITSTATUS(status);
		else
			data->exit_code = 1;
	}
	return (tmp);
}

int	executing(t_data *data)
{
	t_cmd	*tmp;
	int		prev_pipe_read;
	int		fd[2];
	pid_t	pid;

	data->error = NO_TYPE;
	prev_pipe_read = -1;
	if (!data->commands)
		return (0);
	if (data->commands->type == PIPE)
	{
		printf("Syntax error\n");
		return (0);
	}
	tmp = data->commands;
	while (tmp && tmp->value)
	{
		if (ft_pipe(tmp, fd) || ft_fork(&pid, &prev_pipe_read, fd))
			return (1);
		if (pid == 0)
			child(tmp, &prev_pipe_read, fd, data);
		tmp = parent(&prev_pipe_read, fd, tmp, data);
	}
	return (0);
}
