/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:44:39 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/03 16:06:23 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char **envp)
{
	char	*line_read;

	////////////////////////
	(void)argc;
	(void)argv;
	(void)envp;
	////////////////////////

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