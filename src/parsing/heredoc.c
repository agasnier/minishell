/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 17:16:26 by algasnie          #+#    #+#             */
/*   Updated: 2026/03/09 18:04:06 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_heredoc_child(t_minishell *minishell,
	t_token *token_next, int fd[2])
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	close(fd[0]);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_printf(STDERR_FILENO, "minishell: warning: here-document delimited \
by end-of-file (wanted `%s')\n", token_next->token);
			break ;
		}
		if (ft_strcmp(line, token_next->token) == 0)
		{
			free(line);
			break ;
		}
		if (token_next->quoted == 0)
			line = token_expands(minishell, line, 1);
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
	close(fd[1]);
	exit(0);
}

int	handle_heredoc(t_minishell *minishell, t_token *token_next)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) == -1)
		return (1);
	pid = fork();
	if (pid == 0)
		handle_heredoc_child(minishell, token_next, fd);
	close(fd[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, handle_signal);
	if (WIFSIGNALED(status))
	{
		close(fd[0]);
		write(1, "\n", 1);
		minishell->exit_status = 130;
		return (-1);
	}
	return (fd[0]);
}
