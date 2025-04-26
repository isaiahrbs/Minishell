/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:41:59 by dimatayi          #+#    #+#             */
/*   Updated: 2025/04/26 09:30:55 by irobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	here_doc(t_cmd **tmp, int *infile, t_data *data)
{
	if (!(*tmp)->next)
	{
		printf("minishell: syntax error near unexpected token\n");
		exit(1);
	}
	handle_heredoc((*tmp)->next->value, infile, data);
	(*tmp) = (*tmp)->next->next;
	return (1);
}

void	init_var(char ***cmd, char **executable, int *infile, int *outfile)
{
	*infile = 0;
	*outfile = 1;
	*cmd = NULL;
	*executable = NULL;
}

void	handle_child_status(int status, t_data *data)
{
	if (WIFEXITED(status))
		data->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			write(1, "\n", 1);
			data->exit_code = 130;
		}
		else if (WTERMSIG(status) == SIGQUIT)
		{
			write(1, "Quit (core dumped)\n", 20);
			data->exit_code = 131;
		}
	}
}

int	count_tokens(t_token *env_tmp)
{
	int	i;

	i = 0;
	while (env_tmp)
	{
		i++;
		env_tmp = env_tmp->next;
	}
	return (i);
}

int	env_list_into_char_table(t_data *data)
{
	int		i;
	int		len;
	t_token	*env_tmp;

	env_tmp = data->env_list;
	data->envp = ft_calloc(count_tokens(env_tmp) + 1, sizeof(char *));
	if (!data->envp)
		return (0);
	i = -1;
	while (env_tmp)
	{
		len = ft_strlen(env_tmp->name) + ft_strlen(env_tmp->content);
		data->envp[++i] = ft_calloc(len + 2, sizeof(char));
		if (!(data->envp[i]))
			return (free_double_ptr(data->envp), 0);
		ft_strncat(data->envp[i], env_tmp->name, ft_strlen(env_tmp->name));
		ft_strncat(data->envp[i], "=", 1);
		ft_strncat
			(data->envp[i], env_tmp->content, ft_strlen(env_tmp->content));
		env_tmp = env_tmp->next;
	}
	return (1);
}
