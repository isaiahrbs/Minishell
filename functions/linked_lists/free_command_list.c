

#include "../../inc/minishell.h"

void	free_command_list(t_data *data)
{
	t_command	*temp;

	while (data->commands)
	{
		temp = data->commands;
		data->commands = data->commands->next;
		if (temp->value)
			free(temp->value);
		free(temp);
	}
}
