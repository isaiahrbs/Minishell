/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 10:59:16 by irobinso          #+#    #+#             */
/*   Updated: 2025/04/09 19:05:56 by irobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//* stats de depart : 25 mars
//* finis le :
//* RETRIES : 7
void	execute_cd(t_data *data)
{
	char *path;

	/* 1. Get target path */
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
			return;
		}
	}

	/* 2. Attempt directory change (let chdir() handle validation) */
	if (chdir(path) == -1)
	{
		fprintf(stderr, "minishell: cd: %s: ", path);
		perror("");
	}
}

//* JE PUE TELLEMENT EN CODE QUE CA MA PRIS 3 HEURES POUR CE CHECKER DE MERDE
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
