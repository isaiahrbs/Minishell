/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:47:04 by irobinso          #+#    #+#             */
/*   Updated: 2025/04/24 20:00:38 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	set_var(char **envp, t_data *data)
{
	data->envp = envp;
	data->exit_code = 0;
	data->temporary_var = NULL;
	data->export_list = NULL;
}

int	increment_shlvl(t_token *env_list)
{
	t_token	*env_tmp;
	int		lvl;

	lvl = 0;
	env_tmp = env_list;
	while (env_tmp)
	{
		if (!ft_strncmp("SHLVL", env_tmp->name, 5))
		{
			lvl = ft_atoi(env_tmp->content) + 1;
			free(env_tmp->content);
			env_tmp->content = ft_itoa(lvl);
			if (!env_tmp->content)
			{
				free_token_list(&env_list);
				return (0);
			}
			break ;
		}
		env_tmp = env_tmp->next;
	}
	return (1);
}
