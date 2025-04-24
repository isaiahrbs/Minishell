/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:39:04 by irobinso          #+#    #+#             */
/*   Updated: 2025/04/24 16:18:40 by irobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	add_input_history(char *input)
{
	if (input && *input)
		add_history(input);
}

char	*get_input(void)
{
	char	*input;
	char	*cwd;
	char	*string;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		exit(EXIT_FAILURE);
	}
	string = ft_strjoin(cwd, "🌍~ ");
	input = readline(string);
	if (!input)
	{
		if (string)
			free(string);
		printf("exit\n");
		exit(0);
	}
	add_input_history(input);
	free(string);
	return (input);
}
