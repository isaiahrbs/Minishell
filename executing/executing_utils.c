/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:41:59 by dimatayi          #+#    #+#             */
/*   Updated: 2025/04/12 00:42:16 by dimatayi         ###   ########.fr       */
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
