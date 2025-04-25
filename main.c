/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:47:04 by irobinso          #+#    #+#             */
/*   Updated: 2025/04/25 15:25:33 by dimatayi         ###   ########.fr       */
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

void	free_end_loop(t_data *data)
{
	free_token_list(&data->token);
	free_command_list(data);
	free_token_list(&data->temporary_var);
}

void	free_end_process(t_data *data)
{
	free_double_ptr(data->envp);
	free_token_list(&data->env_list);
	if (data->export_list && data->export_list->value)
		free_token_list(&data->export_list);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		res;

	(void)argc;
	(void)argv;
	ft_memset(&data, 0, sizeof(t_data));
	set_var(envp, &data);
	init_signal_handlers();
	if (!env_to_token_list(&data))
		return (1);
	data.exit_request = false;
	res = 0;
	while (!res)
	{
		data.input = get_input(&data);
		tokenize(&data);
		check_if_valid(&data);
		command_list(&data);
		res = executing(&data);
		free_end_loop(&data);
		if (data.exit_request == true)
			break ;
	}
	free_end_process(&data);
	exit_with_code(&data);
}
