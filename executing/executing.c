/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:57:27 by dimatayi          #+#    #+#             */
/*   Updated: 2025/03/17 19:53:20 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free(char **executable, char ***cmd)
{
	if (*executable)
	{
		free(*executable);
		*executable = NULL;
	}
	if (*cmd)
		free_double_ptr(*cmd);
}

int	ft_executable(char **executable, char ***cmd, t_data *data)
{
	if (!ft_exec(*executable, *cmd, data->envp))
	{
		ft_free(executable, cmd);
		exit(1);
	}
	return (0);
}

int	child(t_command *tmp, int *prev_pipe_read, int *fd, t_data *data	)
{
	char	**cmd;
	char	*executable;
	int		infile;
	int		outfile;

	infile = 0;
	outfile = 1;
	cmd = NULL;
	executable = NULL;
	while (tmp && tmp->value && tmp->type != PIPE)
	{
		is_cmd(tmp, &executable, &cmd);
		if (is_redirection(tmp, &executable, &cmd))
		{
			redirout_append(tmp, &outfile, &executable, &cmd);
			redirect_in(tmp, &infile, &executable, &cmd);
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	edit_pipe_fd(infile, outfile, prev_pipe_read, fd);
	if (executable)
		ft_executable(&executable, &cmd, data);
	exit(0);
}

t_command	*parent(int *prev_pipe_read, int *fd, t_command *tmp, int *child_failed	)
{
		int		status;
		pid_t	wait_result;

	*child_failed = 0;
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
	while (wait_result > 0)
	{
		if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
			*child_failed = 1;
		wait_result = wait(&status);
	}
	return (tmp);
}

int	executing(t_data *data)
{
	t_command	*tmp;
	int			prev_pipe_read;
	int			fd[2];
	pid_t		pid;
	int			child_failed;

	prev_pipe_read = -1;
	if (!data->commands)
		return (1);
	tmp = data->commands;
	while (tmp && tmp->value)
	{
		if (ft_pipe(tmp, fd))
			return (1);
		if (ft_fork(&pid, &prev_pipe_read, fd))
			return (1);
		if (pid == 0)
			child(tmp, &prev_pipe_read, fd, data);
		tmp = parent(&prev_pipe_read, fd, tmp, &child_failed);
		if (child_failed)
			return (0);
	}
	return (0);
}

//executable argument redirection file pipe
/*[echo hello] [<] [text.txt] [ | ] [ls -l] [>] [output.txt]
[ls -l] [>] [djjfkdsjfjsk skskdjsk] [ | ] [cat text.txt ls cat echo] */