/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:44:49 by irobinso          #+#    #+#             */
/*   Updated: 2025/04/10 15:40:09 by irobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_list(char **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		printf("%s\n", list[i]);
		i++;
	}
}

int	compare_strings(const void *a, const void *b)
{
	return (strcmp(*(const char **)a, *(const char **)b));
}

void	free_temp_env(char **temp_env, int env_size)
{
	int	i;

	i = 0;
	while (i < env_size)
	{
		free(temp_env[i]);
		i++;
	}
	free(temp_env);
}

void	ft_export(t_data *data)
{
	char	**temp_env;
	int		env_size;
	int		i;

	env_size = 0;
	while (data->envp[env_size] != NULL)
		env_size++;
	temp_env = malloc((env_size + 1) * sizeof(char *));
	if (!temp_env)
		return ;
	i = -1;
	while (++i < env_size)
	{
		temp_env[i] = ft_strdup(data->envp[i]);
		if (!temp_env[i])
		{
			free_temp_env(temp_env, i);
			return ;
		}
	}
	temp_env[env_size] = NULL;
	qsort(temp_env, env_size, sizeof(char *), compare_strings);
	i = 0;
	print_list(temp_env);
	free_temp_env(temp_env, env_size);
}
