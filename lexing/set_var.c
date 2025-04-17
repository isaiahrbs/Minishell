/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:47:04 by irobinso          #+#    #+#             */
/*   Updated: 2025/04/18 00:27:26 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	set_var(char **envp, t_data *data)
{
	data->envp = envp;
	data->exit_code = 0;
	data->envp_copy = NULL;
	data->temporary_var = NULL;
}

int	copy_envp(t_data *data)
{
	int		i;

	i = 0;
	while (data->envp[i])
		i++;
	data->envp_copy = ft_calloc(i + 1, sizeof(char *));
	if (!data->envp_copy)
		return (0);
	i = 0;
	while (data->envp[i])
	{
		data->envp_copy[i] = ft_strdup(data->envp[i]);
		if (!data->envp_copy[i])
		{
			free_double_ptr(data->envp_copy);
			return (0);
		}
		i++;
	}
	return (1);
}

int		increment_shlvl_in_list(t_token *env_list, char **envp_copy)
{
	t_token	*env_tmp;
	int		lvl;

	lvl = 0;
	env_tmp = env_list;
	while (env_tmp)
	{
		if (!ft_strncmp("SHLVL", env_tmp->name, 5))
		{
			lvl = atoi(env_tmp->content) + 1;
			free(env_tmp->content);
			env_tmp->content = ft_itoa(lvl);
			if (!env_tmp->content)
				return (0);
			break ;
		}
		env_tmp = env_tmp->next;
	}
	if (!increment_shlvl_double_char(env_tmp, envp_copy))
		return (0);
	return (1);
}

int		increment_shlvl_double_char(t_token *shlvl, char **envp_copy)
{
	int	i;
	int	len;

	i = 0;
	if (!shlvl || !envp_copy)
		return (0);
	len = ft_strlen(shlvl->name) + ft_strlen(shlvl->content) + 2;
	while (envp_copy[i])
	{
		if (envp_copy[i] && !ft_strncmp("SHLVL", envp_copy[i], 5))
		{
			free(envp_copy[i]);
			envp_copy[i] = ft_calloc(len, sizeof(char));
			if (!envp_copy[i])
				return (0);
			ft_strncat(envp_copy[i], "SHLVL=", 6);
			ft_strncat(envp_copy[i], shlvl->content, ft_strlen(shlvl->content));
			break ;
		}
		i++;
	}
	return (1);
}
