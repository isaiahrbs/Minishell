/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:05:40 by dimatayi          #+#    #+#             */
/*   Updated: 2025/03/17 18:50:23 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_content(char *s)
{
	int		i;
	int		j;
	char		*output;

	i = 0;
	j = 0;
	while (s[i] && s[i] != '=')
		i++;
	i++;
	while (s[i + j] && s[i + j] != 34)
		j++;
	output = ft_calloc(j + 1, sizeof(char));
	if (!output)
		return (NULL);
	ft_strncat(output, s + i, j);
	return (output);
}

char	*ft_name(char *s)
{
	int		i;
	char	*output;

	i = 0;
	if (s[0] == 34)
		s++;
	while (s[i] && s[i] != '=')
		i++;
	output = ft_calloc(i + 1, sizeof(char));
	if (!output)
		return (NULL);
	ft_strncat(output, s, i);
	return (output);
}

int	ft_env(t_data *data)
{
	int	i;

	data->env_list = NULL;
	i = 0;
	/* if (!data->envp)
		return (0); */
	while (data->envp[i])
	{
		if (!ft_assign(data->envp[i], &data->env_list))
		{
			//free something
			return (0);
		}
		i++;
	}
	return (1);
}
