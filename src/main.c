/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:44:39 by algasnie          #+#    #+#             */
/*   Updated: 2026/03/11 15:06:35 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	read_line(t_minishell *minishell)
{
	char		*line_read;

	while (1)
	{
		line_read = readline("minishell> ");
		if (g_receive_message == SIGINT)
		{
			minishell->exit_status = 130;
			g_receive_message = 0;
		}
		if (!line_read)
		{
			printf("exit\n");
			break ;
		}
		if (line_read[0] != '\0')
		{
			add_history(line_read);
			parsing_prompt(minishell, line_read);
			if (minishell->cmds)
				exec_command(minishell);
			ft_lstclear(&minishell->cmds, free_cmds);
		}
		free(line_read);
	}
}

static void	minishell_init_struct(t_minishell *minishell, char **envp)
{
	minishell->exit_status = 0;
	minishell->env = init_env(envp);
	minishell->exec_path_tab = NULL;
	minishell->token_list = NULL;
	minishell->cmds = NULL;
}

int	main(int argc, char *argv[], char **envp)
{
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	minishell_init_struct(&minishell, envp);
	read_line(&minishell);
	free_all(&minishell);
	return (minishell.exit_status);
}
