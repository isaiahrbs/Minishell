/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_and_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:42:46 by dimatayi          #+#    #+#             */
/*   Updated: 2025/04/19 13:24:31 by irobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_echo(char **executable, char ***cmd, t_data *data)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	while ((*cmd)[i])
	{
		if (ft_strncmp(data->token->next->value, "$?", 2) == 0)
		{
			printf("%i", data->exit_code);
			break;
		}
		if (!ft_strncmp((*cmd)[i], "-n", 2) && (*cmd)[i][2] == '\0')
		{
			n = 1;
			i++;
			continue ;
		}
		else if (!ft_strncmp((*cmd)[i], "-n", 2) && (*cmd)[i][2] == 'n')
		{
			i++;
			continue ;
		}
		else if ((*cmd)[i][0] == 34 || (*cmd)[i][0] == 39)
			write(1, (*cmd)[i] + 1, ft_strlen((*cmd)[i] + 1) - 1);
		else
			write(1, (*cmd)[i], ft_strlen((*cmd)[i]));
		i++;
		if ((*cmd)[i])
			write(1, " ", 1);
	}
	if (!n)
	write(1, "\n", 1);
	ft_free(executable, cmd);
	exit(0);
}


void	ft_env(t_data *data, char **executable, char ***cmd)
{
	t_token	*env_var;

	env_var = data->env_list;
	while (env_var && env_var->name && env_var->content)
	{
		printf("%s=%s\n", env_var->name, env_var->content);
		env_var = env_var->next;
	}
	ft_free(executable, cmd);
	exit(0);
}
