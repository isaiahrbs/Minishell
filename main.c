/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:47:04 by irobinso          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/03/17 19:18:26 by irobinso         ###   ########.fr       */
=======
<<<<<<< HEAD
/*   Updated: 2025/03/17 19:21:16 by dimatayi         ###   ########.fr       */
=======
/*   Updated: 2025/03/17 19:18:26 by irobinso         ###   ########.fr       */
>>>>>>> 2489e1a (stp march)
>>>>>>> 543aed90e3c283ddd2ecc84028048dede5f8598e
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		res;
	//t_token	*token_list_head;
	//t_env	*env_head;

	if (argc != 1 || !argv[0])
		return (1);
	data.envp = envp;
	data.temporary_var = NULL;
	init_signal_handlers();
	init_terminal();
	if (!ft_env(&data) || !envp || !envp[0])
		return (1);
	while (1)
	{
		data.input = get_input();
		tokenize(&data);
		check_if_valid(&data);//* dans parsing file
		//print_chained_list(data.token);
		command_list(&data);
<<<<<<< HEAD
		//print_chained_list(data.token);
=======
<<<<<<< HEAD
=======
		//print_chained_list(data.token);
>>>>>>> 2489e1a (stp march)
>>>>>>> 543aed90e3c283ddd2ecc84028048dede5f8598e
		print_command_list(data.commands);
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
	free_token_list(&data.env_list);
	//free_env_list(env_head);
	return (0);
}
