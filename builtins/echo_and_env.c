/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_and_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:42:46 by dimatayi          #+#    #+#             */
/*   Updated: 2025/05/06 15:40:07 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_redirect(t_token *token)
{
	return (token->type == REDIRECT_IN || token->type == REDIRECT_OUT
		|| token->type == APPEND || token->type == HERE_DOC);
}

static void	print_echo(t_token *token)
{
	while (token && !is_redirect(token))
	{
		printf("%s", token->value);
		if (token->next && !is_redirect(token->next))
			printf(" ");
		token = token->next;
	}
}

void	ft_echo(char **executable, char ***cmd, t_data *data)
{
	t_token	*token;
	int		n;

	n = 1;
	token = data->token;
	if (token->next)
		token = token->next;
	else
	{
		printf("\n");
		ft_free(executable, cmd);
		exit(0);
	}
	if (!ft_strncmp(token->value, "-n", 2))
	{
		n = 0;
		token = token->next;
	}
	print_echo(token);
	if (n)
		printf("\n");
	ft_free(executable, cmd);
	exit(0);
}

void	ft_env(t_data *data, char **executable, char ***cmd)
{
	t_token	*env_var;

	env_var = data->env_list;
	while (env_var && env_var->name && env_var->content)
	{
		printf("%s=%s\n", env_var->name, env_var->content);
		env_var = env_var->next;
	}
	ft_free(executable, cmd);
	exit(0);
}
