/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:44:39 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/03 18:15:43 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void print_env(t_env *env)
{
	t_env	*current;
	
	current = env;
	while (1)
	{
		printf("KEY == %s\nVALUE == %s \n\n", current->key, current->value);

		if (!current->next)
			break ;
		current = current->next;
	}
}

int main(int argc, char *argv[], char **envp)
{
	char	*line_read;
	t_env	*env;

	////////////////////////
	(void)argc;
	(void)argv;
	////////////////////////


	env = init_env(envp);
	print_env(env);
	
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