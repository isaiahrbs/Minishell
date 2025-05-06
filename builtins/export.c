/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:44:49 by irobinso          #+#    #+#             */
/*   Updated: 2025/05/06 15:42:09 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
			if (cur->name && cur->next->name
				&& strcmp(cur->name, cur->next->name) > 0)
			{
				swap_token_values(cur, cur->next);
				swapped = 1;
			}
			cur = cur->next;
		}
	}
}

t_token	*copy_list(t_token *original)
{
	t_token	*new_head;
	t_token	*current;
	t_token	*new_node;

	new_head = NULL;
	current = original;
	while (current)
	{
		new_node = malloc(sizeof(t_token));
		if (!new_node)
			return (NULL);
		ft_memset(new_node, 0, sizeof(t_token));
		new_node->content = ft_strdup(current->content);
		new_node->name = current->name;
		ft_lstadd_back(&new_head, new_node);
		current = current->next;
	}
	return (new_head);
}

void	print_line(t_data *data)
{
	printf("declare -x ");
	printf("%s", data->export_list->name);
	printf("=\"%s\"\n", data->export_list->content);
}

void	ft_export(t_data *data, char **executable, char ***cmd)
{
	t_cmd	*current;

	current = data->commands;
	if (!current || !current->value)
		return ;
	if (!ft_strncmp(current->value, "export", 6)
		&& (!current->next || current->next->type == PIPE
			|| current->next->type == REDIRECT_OUT))
	{
		data->export_list = copy_list(data->env_list);
		if (!data->export_list)
		{
			printf("export: failed to copy environment list\n");
			return ;
		}
		bubble_sort_token_list(data->export_list);
		while (data->export_list && data->export_list->name
			&& data->export_list->content)
		{
			print_line(data);
			data->export_list = data->export_list->next;
		}
		ft_free(executable, cmd);
		exit(0);
	}
}
