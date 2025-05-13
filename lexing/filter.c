/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:10:16 by irobinso          #+#    #+#             */
/*   Updated: 2025/05/13 20:53:08 by irobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* void	annoying_cases(t_token *token)
{

	if (token && ft_strncmp(token->value, "\'\"\'", 3) == 0)
	{
		if (token->prev && ft_strncmp(token->prev->value, "echo", 4) == 0)
			printf("\"\n");
		else
			printf("command not found.\n");
		token->content = ft_strdup("need_to_free");
	}
	else if (token && ft_strncmp(token->value, "\"\'\"", 3) == 0)
	{
		if (token->prev && ft_strncmp(token->prev->value, "echo", 4) == 0)
			printf("\'\n");
		else
			printf("command not found.\n");
		token->content = ft_strdup("need_to_free");
	}
} */

int	check_quote_type(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\'')
			return (1);
		if (str[i] == '\"')
			return (2);
		i++;
	}
	return (0);
}

char	get_first_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (str[i]);
		i++;
	}
	return (0);
}

char	*quotes_remover(t_token *token, char quote)
{
	char	*str;
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = token->value;
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] != quote)
		{
			result[j] = str[i];
			j++;
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}

void	remove_quotes(t_token *token)
{
	char	purge_quote;
	char	*result;

	purge_quote = get_first_quote(token->value);
	if (purge_quote == '\'')
		token->quote_type = 1;
	else if (purge_quote == '"')
		token->quote_type = 2;
	else
		token->quote_type = 0;
	result = quotes_remover(token, purge_quote);
	if (result)
	{
		free(token->value);
		token->value = result;
	}
}

void	filter(t_token *token)
{
	if (ft_strncmp(token->value, "export", 6) == 0)
		return ;
	while (token)
	{
		remove_quotes(token);
		token = token->next;
	}
}
