/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:10:16 by irobinso          #+#    #+#             */
/*   Updated: 2025/04/17 20:32:49 by irobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#include "minishell.h"
/*
char	*get_env_value(char *key, t_data *data)
{
	t_token	*env = data->env_list;
	size_t	key_len = ft_strlen(key);

	while (env)
	{
		if (ft_strncmp(env->value, key, key_len) == 0 && env->value[key_len] == '=')
			return (env->value + key_len + 1);
		env = env->next;
	}
	return ("");
}

char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

char	*manage_dollar(char *str, t_data *data)
{
	char	*result = malloc(1);
	size_t	i = 0;
	char	var[1024];
	char	*value;

	if (!result)
		return (NULL);
	result[0] = '\0';

	while (str[i])
	{
		if (str[i] == '$' && (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
		{
			i++;
			size_t k = 0;
			while (ft_isalnum(str[i]) || str[i] == '_')
				var[k++] = str[i++];
			var[k] = '\0';
			value = get_env_value(var, data);
			result = ft_strjoin_free(result, value);
		}
		else
		{
			char tmp[2] = {str[i++], 0};
			result = ft_strjoin_free(result, tmp);
		}
	}
	return (result);
}
*/
void	filter(t_token *token)
{
	char	*src;
	char	*dst;
	int		i;
	int		j;
	char	quote;

	src = token->value;
	dst = malloc(ft_strlen(src) + 1);
	if (!dst)
		return ;
	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i] == '\'' || src[i] == '"')
		{
			quote = src[i++];
			while (src[i] && src[i] != quote)
				dst[j++] = src[i++];
			if (src[i] == quote)
				i++;
		}
		else
			dst[j++] = src[i++];
	}
	dst[j] = '\0';
	free(token->value);
	token->value = dst;
}

