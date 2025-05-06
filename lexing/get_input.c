/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:39:04 by irobinso          #+#    #+#             */
/*   Updated: 2025/05/06 15:54:09 by irobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	add_input_history(char *input)
{
	if (input && *input)
		add_history(input);
}

void	free_shit(t_data *data)
{
	free_end_loop(data);
	free_end_process(data);
}

void	error_exit(void)
{
	perror("ft_strjoin");
	exit(EXIT_FAILURE);
}

char	*get_input(t_data *data)
{
	char	*input;
	char	*cwd;
	char	*string;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		error_exit();
	string = ft_strjoin(cwd, "🌍~ ");
	free(cwd);
	if (!string)
		error_exit();
	input = readline(string);
	free(string);
	if (!input)
	{
		printf("exit\n");
		free_shit(data);
		exit(0);
	}
	add_input_history(input);
	return (input);
}
