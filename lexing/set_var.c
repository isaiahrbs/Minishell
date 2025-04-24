/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:47:04 by irobinso          #+#    #+#             */
/*   Updated: 2025/04/24 19:21:31 by dimatayi         ###   ########.fr       */
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

int		increment_shlvl_in_list(t_token *env_list/* , char **envp_copy */)
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
				return (0);
			break ;
		}
		env_tmp = env_tmp->next;
	}
	return (1);
}

/* if (!increment_shlvl_in_list(data->env_list))
{
	if (data->created_new_env)
		free_double_ptr(data->envp);
	free_token_list(&data->env_list);
	return (0);
} */