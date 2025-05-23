/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:05:40 by dimatayi          #+#    #+#             */
/*   Updated: 2025/05/06 15:48:57 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_content(char *s)
{
	int		i;
	int		j;
	char	*output;

	i = 0;
	j = 0;
	while (s[i] && s[i] != '=')
		i++;
	i++;
	if (s[i] == 34)
		i++;
	while (s[i + j] && s[i + j] != 34)
		j++;
	output = ft_calloc(j + 1, sizeof(char));
	if (!output)
		return (NULL);
	ft_strncat(output, s + i, j);
	return (output);
}

char	*ft_name(char *s)
{
	int		i;
	char	*output;

	i = 0;
	if (s[0] == 34)
		s++;
	while (s[i] && s[i] != '=')
		i++;
	output = ft_calloc(i + 1, sizeof(char));
	if (!output)
		return (NULL);
	ft_strncat(output, s, i);
	return (output);
}

char	**free_failed_env(char **new_env, char *pwd)
{
	if (new_env)
		free_double_ptr(new_env);
	if (pwd)
		free(pwd);
	return (NULL);
}

char	**create_env(void)
{
	char	**new_env;
	char	*pwd;

	new_env = NULL;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (NULL);
	new_env = ft_calloc(5, sizeof(char *));
	if (!new_env)
		return (free_failed_env(new_env, pwd));
	new_env[0] = ft_strdup("SHLVL=1");
	if (!new_env[0])
		return (free_failed_env(new_env, pwd));
	new_env[1] = ft_strdup("PATH=/bin:/sbin:/usr/bin:/usr/sbin");
	if (!new_env[1])
		return (free_failed_env(new_env, pwd));
	new_env[2] = ft_strdup("TERM=xterm-256color");
	if (!new_env[2])
		return (free_failed_env(new_env, pwd));
	new_env[3] = ft_strjoin("PWD=", pwd);
	if (!new_env[3])
		return (free_failed_env(new_env, pwd));
	free(pwd);
	return (new_env);
}

int	env_to_token_list(t_data *data)
{
	int	i;

	i = 0;
	data->env_list = NULL;
	if (!getenv("PATH") || !getenv("TERM") || !getenv("PWD"))
	{
		data->envp = create_env();
		if (!data->envp)
			return (0);
		data->created_new_env = 1;
	}
	while (data->envp[i])
	{
		if (!ft_assign(data->envp[i], &data->env_list))
			return (free_dbl_ptr_and_tkn_list(data));
		i++;
	}
	if (!increment_shlvl(data->env_list))
		return (free_dbl_ptr_and_tkn_list(data));
	if (data->created_new_env)
		free_double_ptr(data->envp);
	data->envp = NULL;
	return (1);
}
