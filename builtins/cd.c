/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 10:59:16 by irobinso          #+#    #+#             */
/*   Updated: 2025/04/10 17:21:07 by irobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	execute_cd(t_data *data)
{
	char	*path;

	if (data->token->next != NULL && data->token->next->value != NULL)
	{
		path = data->token->next->value;
	}
	else
	{
		path = getenv("HOME");
		if (path == NULL)
		{
			fprintf(stderr, "minishell: cd: HOME not set\n");
			return ;
		}
	}
	if (chdir(path) == -1)
	{
		fprintf(stderr, "minishell: cd: %s: ", path);
		perror("");
	}
}

int	checker(t_token *token)
{
	if (is_equal(token->value, "cd"))
		return (1);
	return (0);
}

void	handle_cd_command(t_data *data)
{
	t_token	*current;

	current = data->token;
	if (!checker(current))
		return ;
	execute_cd(data);
	free_token_list(&data->token);
}
