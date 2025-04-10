/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:39:04 by irobinso          #+#    #+#             */
/*   Updated: 2025/04/10 20:12:07 by irobinso         ###   ########.fr       */
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
		printf("exit\n");
		exit(0);
	}
	if (is_equal(input, "exit") != 0)
	{
		printf("Closed Minishell.\n");
		exit(EXIT_SUCCESS);
	}
	add_input_history(input);
	free(string);
	return (input);
}
