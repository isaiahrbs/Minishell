/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:37:06 by irobinso          #+#    #+#             */
/*   Updated: 2025/04/17 20:51:01 by irobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}

void	handle_exit_command(t_data *data)
{
	t_token	*current;

	if (ft_strncmp("exit", data->token->value, 4) == 0)
	{
		if (data->token->next)
		{
			current = data->token;
			current = current->next;
			if (ft_isdigit(ft_atoi(current->value)))
				data->exit_code = ft_atoi(current->value);
			printf("exit code : %i\nmais cheppa comment faire en sorte que ca se rappelle ptnnnn\nfonction est dans tokenizer sj\n\n", data->exit_code);
		}
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	return ;
}
