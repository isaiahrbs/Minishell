/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:41:59 by dimatayi          #+#    #+#             */
/*   Updated: 2025/04/16 14:39:16 by irobinso         ###   ########.fr       */
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


/* void	env_list_to_double_char(t_data *data)
{

} */
