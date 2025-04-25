/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:39:04 by irobinso          #+#    #+#             */
/*   Updated: 2025/04/25 14:05:35 by dimatayi         ###   ########.fr       */
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
	free(cwd);
	if (!string)
	{
		perror("ft_strjoin");
		exit(EXIT_FAILURE);
	}
	input = readline(string);
	if (!input)
	{
		printf("exit\n");
		exit(0);
	}
	add_input_history(input);
	return (input);
}
