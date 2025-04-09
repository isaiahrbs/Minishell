/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:39:04 by irobinso          #+#    #+#             */
/*   Updated: 2025/04/09 09:23:15 by irobinso         ###   ########.fr       */
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
	char	cwd[200];
	char	*string;

	getcwd(cwd, sizeof(cwd));
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
	return (input);
}
