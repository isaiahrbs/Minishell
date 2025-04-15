/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:47:04 by irobinso          #+#    #+#             */
/*   Updated: 2025/04/15 11:25:05 by irobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_command_list(t_cmd *head)
{
	t_cmd	*current;

	current = head;
	while (current)
	{
		printf("Command: %s\n", current->value);
		current = current->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		res;

	(void)argc;
	(void)argv;
	set_var(envp, &data);
	init_signal_handlers();
	if (!env_to_token_list(&data))
		return (1);
	res = 0;
	while (!res)
	{
		data.input = get_input();
		tokenize(&data);
		check_if_valid(&data);
		command_list(&data);
		res = executing(&data);
		free_token_list(&data.token);
		free_command_list(&data);
		free_token_list(&data.temporary_var);
		free_token_list(&data.export_list);
	}
	if (data.created_new_env)
		free_double_ptr(data.envp);
	free_token_list(&data.env_list);
	return (0);
}
