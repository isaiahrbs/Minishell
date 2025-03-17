/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 01:33:05 by dimatayi          #+#    #+#             */
/*   Updated: 2025/03/17 18:40:38 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	edit_pipe_fd(int infile, int outfile, int *prev_pipe_read, int *fd)
{
	if (infile != 0)
	{
		dup2(infile, 0);
		close(infile);
	}
	if (outfile != 1)
	{
		dup2(outfile, 1);
		close(outfile);
	}
	if (*prev_pipe_read != -1)
	{
		dup2(*prev_pipe_read, 0);
		close(*prev_pipe_read);
	}
	if (fd[1] != -1)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
	}
}

int	ft_pipe(t_command *tmp, int *fd)
{
	t_command	*next_cmd;

	fd[0] = -1;
	fd[1] = -1;
	next_cmd = tmp;
	while (next_cmd && next_cmd->value && next_cmd->type != PIPE)
		next_cmd = next_cmd->next;
	if (next_cmd && next_cmd->type == PIPE)
	{
		if (pipe(fd) == -1)
		{
			perror("");
			return (1);
		}
	}
	return (0);
}

int	ft_fork(pid_t *pid, int *prev_pipe_read, int *fd)
{
	*pid = fork();
	if (*pid == -1)
	{
		perror("fork error\n");
		if (*prev_pipe_read != -1)
			close(*prev_pipe_read);
		if (fd[0] != -1)
		{
			close(fd[0]);
			close(fd[1]);
		}
		return (1);
	}
	return (0);
}