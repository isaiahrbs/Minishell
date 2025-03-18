/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_metachar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:12:04 by irobinso          #+#    #+#             */
/*   Updated: 2025/03/18 03:04:04 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_metachar_type(int type)
{
	if (type == PIPE || type == REDIRECT_IN || type == REDIRECT_OUT)
		return (1);
	if (type == APPEND || type == HERE_DOC)
		return (1);
	return (0);
}

int	is_metachar_value(char *s)
{
	int i;

	i = 0;
	if (s[i] == '|' || s[i] == '&' || s[i] == ';' || s[i] == '('
		|| s[i] == ')' || s[i] == '<' || s[i] == '>')
		return (1);
	return (0);
}
