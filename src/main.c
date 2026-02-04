/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:44:39 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/04 18:36:46 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char **envp)
{
	char		*line_read;
	t_minishell	minishell;

	////////////////////////
	(void)argc;
	(void)argv;
	////////////////////////

	minishell.env = init_env(envp);
	//minishell.path = get_exec_path(&minishell);
	
	///test environnement///
	test_print_env(minishell.env);
	// test_print_env_value(env, "PATH");
	/////////
	
	while (1)
	{
		line_read = readline("minishell> ");

		if (!line_read)
		{
			printf("exit\n");
			break ;
		}

		if (line_read[0] != '\0')
			add_history(line_read);

		free(line_read);
	}
	
}