/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:44:49 by irobinso          #+#    #+#             */
/*   Updated: 2025/04/10 00:21:44 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	get_length(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	ft_export(t_data *data)
{
	char	**temp_env;
	int		length;
	int		i;

	i = 0;
	temp_env = malloc(sizeof(char *) * (data->envp + 1));
	if (!temp_env)
	{
		printf("error: Malloc temp_emv");
		exit(EXIT_FAILURE);
	}
	length = get_length(data->envp);
	while (i <= length)
	{

	}
	return ;
}
