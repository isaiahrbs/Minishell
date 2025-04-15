/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:47:04 by irobinso          #+#    #+#             */
/*   Updated: 2025/04/15 19:31:17 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	set_var(char **envp, t_data *data)
{
	data->envp = envp;
	data->exit_code = 0;
	data->custom_envp = NULL;
	data->temporary_var = NULL;
}
