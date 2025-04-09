/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:57:27 by dimatayi          #+#    #+#             */
/*   Updated: 2025/04/09 11:36:10 by irobinso         ###   ########.fr       */
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
	if (!strcmp("env", *executable))
		ft_env(data, executable, cmd);
	if (!strcmp("echo", *executable))
		ft_echo(executable, cmd);
	if (!ft_exec(*executable, *cmd, data))
		ft_free(executable, cmd);
	if (!strcmp("<<", *executable))
		ft_echo(executable, cmd);
	if (data->error == MALLOC_ERROR)
		exit(1);
	printf("command not found\n");
	exit(1);
}

int	child(t_command *tmp, int *prev_pipe_read, int *fd, t_data *data)
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
		if (tmp->type == HERE_DOC)
		{
			if (!tmp->next)
			{
				printf("minishell: syntax error near unexpected token\n");
				exit(1);
			}
			handle_heredoc(tmp->next->value, &infile);
			tmp = tmp->next->next;
			continue;
		}
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
	exit(1);
}

t_command	*parent(int *prev_pipe_read, int *fd, t_command *tmp, t_data *data)
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
	t_command	*tmp;
	int			prev_pipe_read;
	int			fd[2];
	pid_t		pid;

	data->error = NO_TYPE;
	prev_pipe_read = -1;
	if (!data->commands)
		return (0);
	tmp = data->commands;
	while (tmp && tmp->value)
	{
		if (ft_pipe(tmp, fd))
			return (1);
		if (ft_fork(&pid, &prev_pipe_read, fd))
			return (1);
		if (pid == 0)
			child(tmp, &prev_pipe_read, fd, data);
		tmp = parent(&prev_pipe_read, fd, tmp, data);
	}
	return (0);
}

//executable argument redirection file pipe
/*[echo hello] [<] [text.txt] [ | ] [ls -l] [>] [output.txt]
[ls -l] [>] [djjfkdsjfjsk skskdjsk] [ | ] [cat text.txt ls cat echo] */
