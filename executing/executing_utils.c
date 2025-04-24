/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:41:59 by dimatayi          #+#    #+#             */
/*   Updated: 2025/04/24 17:05:28 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free(char **executable, char ***cmd)
{
	if (*executable)
	{
		free(*executable);
		*executable = NULL;
	}
	if (*cmd)
		free_double_ptr(*cmd);
}

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
int	env_list_into_char_table(t_data *data)
{
	int		i;
	int		j;
	int		len_name;
	int		len_content;
	t_token	*env_tmp;

	i = 0;
	j = 0;
	env_tmp = data->env_list;
	while (env_tmp)
	{
		i++;
		env_tmp = env_tmp->next;
	}
	data->envp = ft_calloc(i + 1, sizeof(char *));
	if (!data->envp)
		return (0);
	env_tmp = data->env_list;
	while (env_tmp)
	{
		len_name = ft_strlen(env_tmp->name);
		len_content = ft_strlen(env_tmp->content);
		data->envp[j] = ft_calloc(len_name + len_content + 2, sizeof(char));
		if (!(data->envp[j]))
		{
			free_double_ptr(data->envp);
			return(0);
		}
		ft_strncat(data->envp[j], env_tmp->name, len_name);
		ft_strncat(data->envp[j], "=", 1);
		ft_strncat(data->envp[j], env_tmp->content, len_content);
		j++;
		env_tmp = env_tmp->next;
	}
	return (1);
}
