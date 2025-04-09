/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:50:37 by irobinso          #+#    #+#             */
/*   Updated: 2025/04/09 20:21:33 by irobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_heredoc(char *delimiter, int *infile)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
	{
		perror("minishell: pipe");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		line = readline("► ");
		if (!line)
		{
			printf("minishell: warning: here-document delimited by end-of-file\n");
			break;
		}
		if (is_equal(line, delimiter) != 0)
		{
			free(line);
			break;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	*infile = pipefd[0];
}
