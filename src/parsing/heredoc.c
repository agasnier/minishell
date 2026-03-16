/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 17:16:26 by algasnie          #+#    #+#             */
/*   Updated: 2026/03/16 12:34:35 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	g_receive_message = SIGINT;
	close(STDIN_FILENO);
}

static int	read_heredoc_line(t_minishell *minishell,
	t_token *token_next, int *fd)
{
	char	*line;

	line = readline("> ");
	if (!line)
	{
		if (g_receive_message == SIGINT)
			return (0);
		ft_printf(STDERR_FILENO, "minishell: warning: here-document delimited \
by end-of-file (wanted `%s')\n", token_next->token);
		return (0);
	}
	if (ft_strcmp(line, token_next->token) == 0)
	{
		free(line);
		return (0);
	}
	if (token_next->quoted == 0)
		line = token_expands(minishell, line, 1);
	ft_putendl_fd(line, fd[1]);
	free(line);
	return (1);
}

static void	handle_heredoc_child(t_minishell *minishell,
	t_token *token_next, int fd[2])
{
	signal(SIGINT, handle_sigint_heredoc);
	close(fd[0]);
	while (1)
	{
		if (!read_heredoc_line(minishell, token_next, fd))
			break ;
	}
	close(fd[1]);
	free_all(minishell);
	if (g_receive_message == SIGINT)
		exit (130);
	exit(0);
}

int	handle_heredoc(t_minishell *minishell, t_token *token_next)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	token_next->token = remove_token_quotes(token_next->token);
	if (pipe(fd) == -1)
		return (1);
	pid = fork();
	if (pid == 0)
		handle_heredoc_child(minishell, token_next, fd);
	close(fd[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, handle_signal);
	if ((WIFEXITED(status) && WEXITSTATUS(status) == 130)
		|| WIFSIGNALED(status))
	{
		close(fd[0]);
		write(1, "\n", 1);
		minishell->exit_status = 130;
		return (-1);
	}
	return (fd[0]);
}
