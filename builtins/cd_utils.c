/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 10:59:16 by irobinso          #+#    #+#             */
/*   Updated: 2025/05/06 15:47:36 by irobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	change_env_list(t_data *data, char *replace_str, char *oldpwd)
{
	t_token	*current;

	current = data->env_list;
	while (current)
	{
		if (ft_strncmp(current->name, "PWD", 3) == 0)
		{
			ft_memset(current->content, 0, sizeof(current->content));
			current->content = ft_strdup(replace_str);
			break ;
		}
		current = current->next;
	}
	current = data->env_list;
	while (current)
	{
		if (ft_strncmp(current->name, "OLDPWD", 6) == 0)
		{
			ft_memset(current->content, 0, sizeof(current->content));
			current->content = ft_strdup(oldpwd);
			break ;
		}
		current = current->next;
	}
}
