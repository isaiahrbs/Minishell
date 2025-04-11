/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:44:49 by irobinso          #+#    #+#             */
/*   Updated: 2025/04/11 22:58:58 by irobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
/*
void	print_list(char **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		printf("%s\n", list[i]);
		i++;
	}
}

int	compare_strings(const void *a, const void *b)
{
	return (strcmp(*(const char **)a, *(const char **)b));
}

void	free_temp_env(char **temp_env, int env_size)
{
	int	i;

	i = 0;
	while (i < env_size)
	{
		free(temp_env[i]);
		i++;
	}
	free(temp_env);
}

void	ft_export(t_data *data)
{
	char	**temp_env;
	int		env_size;
	int		i;

	env_size = 0;
	while (data->envp[env_size] != NULL)
		env_size++;
	temp_env = malloc((env_size + 1) * sizeof(char *));
	if (!temp_env)
		return ;
	i = -1;
	while (++i < env_size)
	{
		temp_env[i] = ft_strdup(data->envp[i]);
		if (!temp_env[i])
		{
			free_temp_env(temp_env, i);
			return ;
		}
	}
	temp_env[env_size] = NULL;
	qsort(temp_env, env_size, sizeof(char *), compare_strings);
	i = 0;
	print_list(temp_env);
	free_temp_env(temp_env, env_size);
} */

void	swap_token_values(t_token *a, t_token *b)
{
	char	*tmp;

	tmp = a->name;
	a->name = b->name;
	b->name = tmp;
	tmp = a->content;
	a->content = b->content;
	b->content = tmp;
}

void	bubble_sort_token_list(t_token *head)
{
	t_token	*cur;
	int		swapped;

	if (!head)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		cur = head;
		while (cur->next)
		{
			if (strcmp(cur->name, cur->next->name) > 0)
			{
				swap_token_values(cur, cur->next);
				swapped = 1;
			}
			cur = cur->next;
		}
	}
}

t_token *copy_list(t_token *original)
{
	t_token *new_head = NULL;
	t_token *current = original;
	t_token *new_node;

	while (current)
	{
		new_node = malloc(sizeof(t_token));
		if (!new_node)
			return (NULL);
		ft_memset(new_node, 0, sizeof(t_token)); // zero out everything
		new_node->content = ft_strdup(current->value);
		new_node->type = current->type;
		ft_lstadd_back(&new_head, new_node); // your own function to handle linking
		current = current->next;
	}
	return (new_head);
}

void	ft_export(t_data *data, char **executable, char ***cmd)
{
	t_token	*export_var;

	export_var = copy_list(data->env_list);
	if (!export_var)
	{
		//safe_free(export_var);
		printf("export: failed to copy environment list\n");
		return ;
	}
	bubble_sort_token_list(export_var);
	while (export_var && export_var->name && export_var->content)
	{
		printf("%s=%s\n", export_var->name, export_var->content);
		export_var = export_var->next;
	}
	ft_free(executable, cmd);
	exit(0);
}
