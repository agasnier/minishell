/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:44:39 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/17 16:42:51 by algasnie         ###   ########.fr       */
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

	////////// init strcut minishell ///////////////////
	minishell.env = init_env(envp);
	minishell.exec_path_tab = get_exec_path(&minishell);
	////////// init strcut minishell ///////////////////
	
	///test environnement///
	// test_print_env(minishell.env);
	// test_print_env_value(minishell.env, "PATH");
	// test_print_exec_path_tab(minishell.exec_path_tab);
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
		{
			add_history(line_read);
			parsing_prompt(&minishell, line_read);
			
		}

			

		free(line_read);
	}

	free_all(&minishell);
	
}