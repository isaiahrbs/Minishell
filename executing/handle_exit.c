/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:40:26 by irobinso          #+#    #+#             */
/*   Updated: 2025/05/06 15:50:00 by irobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	grab_exit_code(t_data *data, int status)
{
	int	sig;

	if (WIFEXITED(status))
	{
		data->exit_code = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			write(1, "\n", 1);
		else if (sig == SIGQUIT)
			write(1, "Quit (core dumped)\n", 19);
		data->exit_code = 128 + sig;
	}
}

void	exit_with_code(t_data *data)
{
	if (data->exit_request == true)
	{
		if (data->exit_code)
			exit(data->exit_code);
		exit(EXIT_SUCCESS);
	}
}

void	check_exit_request(t_data *data)
{
	if (data->token && ft_strncmp(data->token->value, "exit", 4) == 0)
	{
		if (data->token->next && is_numeric(data->token->next->value))
			data->exit_code = ft_atoi(data->token->next->value);
		data->exit_request = true;
		printf("exit\n");
		free_command_list(data);
	}
}

void	exit_handling(t_data *data)
{
	check_exit_request(data);
}
