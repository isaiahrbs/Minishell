/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 10:59:16 by irobinso          #+#    #+#             */
/*   Updated: 2025/05/06 15:47:44 by irobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	update_pwd_oldpwd(t_data *data, char *oldpwd)
{
	char	*replace_str;

	replace_str = getcwd(NULL, 0);
	if (!replace_str)
	{
		perror("getcwd");
		exit(EXIT_FAILURE);
	}
	change_env_list(data, replace_str, oldpwd);
	free(replace_str);
	if (oldpwd)
		free(oldpwd);
}

char	*get_oldpwd(t_data *data)
{
	t_token	*current;
	char	*copy;

	current = data->env_list;
	while (current)
	{
		if (ft_strncmp(current->name, "PWD", 3) == 0)
		{
			copy = ft_strdup(current->content);
		}
		current = current->next;
	}
	return (copy);
}

void	check_wiggly(char **path, t_data *data)
{
	if (data->token->next && ft_strncmp(data->token->next->value, "~", 1) == 0)
	{
		*path = getenv("HOME");
		if (path == NULL)
		{
			fprintf(stderr, "minishell: cd: HOME not set\n");
			return ;
		}
	}
}

void	execute_cd(t_data *data)
{
	char	*path;
	char	*oldpwd;

	oldpwd = get_oldpwd(data);
	if (data->token->next != NULL && data->token->next->value != NULL)
		path = data->token->next->value;
	else
	{
		path = getenv("HOME");
		if (path == NULL)
		{
			fprintf(stderr, "minishell: cd: HOME not set\n");
			return ;
		}
	}
	check_wiggly(&path, data);
	if (chdir(path) == -1)
	{
		fprintf(stderr, "minishell: cd: %s: ", path);
		perror("");
	}
	else
		update_pwd_oldpwd(data, oldpwd);
}

void	handle_cd_command(t_data *data)
{
	t_token	*current;

	current = data->token;
	if (is_equal(current->value, "cd"))
	{
		execute_cd(data);
		free_token_list(&data->token);
	}
}
