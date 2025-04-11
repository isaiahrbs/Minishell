/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:50:37 by irobinso          #+#    #+#             */
/*   Updated: 2025/04/12 01:17:44 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	expand_to_heredoc(char **line, t_data *data)
{
	char	*var_start;
	int		i;

	i = 0;
	if (!*line)
		return (1);
	while (*line[i])
	{
		if (!ft_strncmp(*line, "$?\0", 3))
		{
			free(*line);
			*line = ft_itoa(data->exit_code);
			if (!*line)
				return (0);
		}
		var_start = is_var(&(*line)[i], &i);
		if (var_start && !scan_var_list(data->env_list, line, var_start))
			return (0);
		else
			break ;
		i++;
	}
	return (1);
}

void	handle_heredoc(char *delimiter, int *infile, t_data *data)
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
			break ;
		}
		if (is_equal(line, delimiter) != 0)
		{
			free(line);
			break ;
		}
		expand_to_heredoc(&line, data);
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	*infile = pipefd[0];
}
