/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:40:43 by dimatayi          #+#    #+#             */
/*   Updated: 2025/04/07 14:29:51 by irobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_valid_name(char *s)
{
	int	i;

	i = 0;
	if (s == NULL || s[i] == '\0')
		return (0);
	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (0);
	i++;
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	is_assignment(char *s)
{
	char	*equal_sign;
	char	*name_part;
	int		result;

	if (s == NULL || *s == '\0' || is_single_quote(s, 1))
		return (0);
	equal_sign = ft_strchr(s, '=');
	if (equal_sign == NULL)
		return (0);
	if (*(equal_sign + 1) == ' ' || *(equal_sign - 1) == ' ')
		return (0);
	s++;
	name_part = ft_strndup(s, equal_sign - s);
	if (name_part == NULL)
		return (0);
	result = is_valid_name(name_part);
	free(name_part);
	return (result);
}

int	is_expansion(char *s)
{
	int	i;

	if (s == NULL || s[0] != '$')
		return (0);
	if (s[1] == '{')
	{
		i = 2;
		while (s[i] && s[i] != '}')
		{
			if (!ft_isalnum(s[i]) && s[i] != '_')
				return (0);
			i++;
		}
		return (s[i] == '}');
	}
	return (0);
}

int	is_substitution(char *s)
{
	int	i;
	int	parenthesis;

	if (s == NULL || s[0] != '$')
		return (0);
	if (s[1] == '(')
	{
		i = 2;
		parenthesis = 1;
		while (s[i] && parenthesis > 0)
		{
			if (s[i] == '(')
				parenthesis++;
			else if (s[i] == ')')
				parenthesis--;
			i++;
		}
		return (parenthesis == 0);
	}
	return (0);
}
