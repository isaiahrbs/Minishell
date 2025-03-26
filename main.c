/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:47:04 by irobinso          #+#    #+#             */
/*   Updated: 2025/03/26 22:04:21 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		res;
	//t_token	*token_list_head;
	//t_env	*env_head;

	(void)argc;
	(void)argv;
	/* if (argc != 1 || !argv[0])
		return (1); */
	data.envp = envp;
	data.temporary_var = NULL;
	init_signal_handlers();
	//init_terminal();
	if (!ft_env(&data))		//j'ai enlevé cet verif: !envp || !envp[0]
		return (1);			//car env -i ./Minishell devrait marcher
	while (1)
	{
		data.input = get_input();
		tokenize(&data);
		check_if_valid(&data);//* dans parsing file
		//print_chained_list(data.token);
		command_list(&data);
		//print_chained_list(data.token);
		//print_chained_list(data.token);
		//print_command_list(data.commands);
		res = executing(&data);
		/* printf("ENVIRONMENT VARIABLES\n");
		print_variable_list(data.env_list);
		printf("TEMPORARY VARIABLES\n");
		print_variable_list(data.temporary_var); */
		//printf("NODE LIST\n");
		//print_chained_list(data.token);
		free_token_list(&data.token);
		free_token_list(&data.temporary_var);
		if (res)	// sortir de la boucle en cas de malloc error
			break ;
	}
	if (data.created_new_env)
		free_double_ptr(data.envp);	//create a function that frees every variable in t_data
	free_token_list(&data.env_list);
	//free_env_list(env_head);
	return (0);
}
