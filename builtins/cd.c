/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 10:59:16 by irobinso          #+#    #+#             */
/*   Updated: 2025/04/11 23:39:31 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	change_env_list(t_data *data, char *replace_str)
{
	t_token	*current;

	current = data->env_list;
	while (current)
	{
		if (ft_strncmp(current->value, "PWD=", 4) == 0)
		{
			ft_memset(current->value, 0, sizeof(current->value));
			current->value = ft_strdup(replace_str);
			break ;
		}
		current = current->next;
	}
}

void	update_pwd_oldpwd(t_data *data)
{
	char	*replace_str;
	int		i;

	replace_str = ft_strjoin("PWD=", getcwd(NULL, 0));
	if (!replace_str)
	{
		perror("getcwd");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], "PWD=", 4) == 0)
		{
			ft_memset(data->envp[i], 0, sizeof(data->envp[i]));
			data->envp[i] = ft_strdup(replace_str);
			change_env_list(data, replace_str);
			break ;
		}
		i++;
	}
	free(replace_str);
}

void	execute_cd(t_data *data)
{
	char	*path;

	if (data->token->next != NULL && data->token->next->value != NULL)
	{
		path = data->token->next->value;
	}
	else
	{
		path = getenv("HOME");
		if (path == NULL)
		{
			fprintf(stderr, "minishell: cd: HOME not set\n");
			return ;
		}
	}
	if (chdir(path) == -1)
	{
		fprintf(stderr, "minishell: cd: %s: ", path);
		perror("");
	}
	else
		update_pwd_oldpwd(data);
}

int	checker(t_token *token)
{
	if (is_equal(token->value, "cd"))
		return (1);
	return (0);
}

void	handle_cd_command(t_data *data)
{
	t_token	*current;

	current = data->token;
	if (!checker(current))
		return ;
	execute_cd(data);
	free_token_list(&data->token);
}
