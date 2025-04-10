/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 01:33:03 by dimatayi          #+#    #+#             */
/*   Updated: 2025/04/10 00:25:56 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_cmd(t_cmd *tmp, char **executable, char ***cmd)
{
	if (tmp->type == WORD)
	{
		*executable = ft_strndup(tmp->value, ft_len(tmp->value, ' '));
		if (!*executable)
		{
			perror("");
			exit(1);
		}
		*cmd = metachar_split(tmp->value);
		if (!*cmd)
		{
			perror("");
			free(*executable);
			*executable = NULL;
			exit(1);
		}
	}
	return (0);
}

int	is_redirection(t_cmd *tmp, char **executable, char ***cmd)
{
	if (tmp->type != APPEND && tmp->type != REDIRECT_IN
		&& tmp->type != REDIRECT_OUT)
		return (0);
	if (!tmp->next || tmp->next->type != WORD)
	{
		printf("syntax error near unexpected token\n");
		ft_free(executable, cmd);
		exit(1);
	}
	return (1);
}

int	redirout_append(t_cmd *tmp, int *outfile, char **exec, char ***cmd)
{
	if (tmp->type != APPEND && tmp->type != REDIRECT_OUT)
		return (0);
	if (*outfile != 1)
		close(*outfile);
	if (tmp->type == REDIRECT_OUT)
		*outfile = open(tmp->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (tmp->type == APPEND)
		*outfile = open(tmp->next->value, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (*outfile == -1)
	{
		perror(tmp->next->value);
		ft_free(exec, cmd);
		exit(1);
	}
	return (1);
}

int	redir_in(t_cmd *tmp, int *infile, char **executable, char ***cmd)
{
	if (tmp->type != REDIRECT_IN)
		return (0);
	if (access(tmp->next->value, R_OK) == -1)
	{
		perror(tmp->next->value);
		ft_free(executable, cmd);
		exit (1);
	}
	if (*infile != 0)
		close(*infile);
	*infile = open(tmp->next->value, O_RDONLY, 0777);
	return (1);
}
