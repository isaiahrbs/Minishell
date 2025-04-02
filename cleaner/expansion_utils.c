/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 23:10:10 by dimatayi          #+#    #+#             */
/*   Updated: 2025/04/01 19:51:55 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_len(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

int	is_single_quote(char *s, int dollar_index)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s[i] && i < dollar_index)
	{
		if (s[i] == 39)
			counter++;
		i++;
	}
	if (counter == 0 || counter % 2 == 0)
		return (0);
	return (1);
}