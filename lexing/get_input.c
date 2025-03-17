/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:39:04 by irobinso          #+#    #+#             */
/*   Updated: 2025/03/16 17:19:19 by irobinso         ###   ########.fr       */
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
	add_input_history(input);
	return (input);
}
