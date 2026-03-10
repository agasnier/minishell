/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:58:27 by masenche          #+#    #+#             */
/*   Updated: 2026/03/10 15:37:24 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_child(t_minishell *minishell, char **env_tab)
{
	free_tab(env_tab);
	free_all(minishell);
}

void	wait_all_children(pid_t last_pid, t_minishell *minishell)
{
	int		status;
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				minishell->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				minishell->exit_status = 128 + WTERMSIG(status);
				if (WTERMSIG(status) == SIGINT)
					write(1, "\n", 1);
				else if (WTERMSIG(status) == SIGQUIT)
					ft_printf(2, "Quit\n");
			}
		}
		pid = wait(&status);
	}
	signal(SIGINT, handle_signal);
}

static void	exit_child(t_cmd *cmd, char **env_tab, t_minishell *minishell)
{
	int	status;

	if (!cmd->args[0])
	{
		free_child(minishell, env_tab);
		exit(0);
	}
	if (is_builtin(cmd->args[0]))
	{
		status = execute_builtin(cmd, minishell);
		signal(SIGINT, handle_signal);
		free_child(minishell, env_tab);
		exit(status);
	}
}

static void	exit_fd(t_cmd *cmd, char **env_tab, t_minishell *minishell)
{
	if (cmd->fd_in == -2 || cmd->fd_out == -2)
	{
		free_child(minishell, env_tab);
		exit(1);
	}
}

void	exe_child(t_cmd *cmd, t_minishell *minishell, char **env_tab)
{
	char	*path_env;

	exit_fd(cmd, env_tab, minishell);
	exe_fd(cmd);
	signal(SIGINT, SIG_DFL);
	signal(SIGPIPE, SIG_IGN);
	exit_child(cmd, env_tab, minishell);
	signal(SIGPIPE, SIG_DFL);
	if (!cmd->cmd_path)
	{
		path_env = get_env_value(minishell, "PATH");
		if (path_env == NULL)
			ft_printf(2, "minishell: %s: No such file or directory\n",
				cmd->args[0]);
		else
			ft_printf(2, "minishell: %s: command not found\n", cmd->args[0]);
		free(path_env);
		free_child(minishell, env_tab);
		exit (127);
	}
	execve(cmd->cmd_path, cmd->args, env_tab);
	ft_printf(2, "minishell: %s: %s", cmd->args[0], strerror(errno));
	free_child(minishell, env_tab);
	exit(126);
}
