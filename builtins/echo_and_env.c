/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_and_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:42:46 by dimatayi          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2025/04/16 20:03:19 by dimatayi         ###   ########.fr       */
=======
/*   Updated: 2025/04/17 19:59:40 by irobinso         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	print_arg(char *arg)
{
	size_t	len;

	if (arg[0] == '"' || arg[0] == '\'')
	{
		len = ft_strlen(arg);
		if (len >= 2)
			write(1, arg + 1, len - 2);
		else
			write(1, "", 0);
	}
	else
		write(1, arg, ft_strlen(arg));
}

static int	handle_n_flag(char **cmd, int *i)
{
	int		n_flag;
	int		j;

	n_flag = 0;
	while (cmd[*i] && !ft_strncmp(cmd[*i], "-n", 2))
	{
		j = 2;
		while (cmd[*i][j] == 'n')
			j++;
		if (cmd[*i][j] == '\0')
			n_flag = 1;
		else
			break ;
		(*i)++;
	}
	return (n_flag);
}

void	ft_echo(char **executable, char ***cmd)
{
	int	i;
	int	n;

	i = 1;
	n = handle_n_flag(*cmd, &i);
	while ((*cmd)[i])
	{
<<<<<<< Updated upstream
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
=======
		print_arg((*cmd)[i]);
		if ((*cmd)[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!n)
		write(1, "\n", 1);
>>>>>>> Stashed changes
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
