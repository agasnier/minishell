/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:16:41 by masenche          #+#    #+#             */
/*   Updated: 2026/03/03 10:00:19 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_child(t_cmd *cmd, t_minishell *minishell, char **env_tab)
{
	int status;

	signal(SIGINT, SIG_DFL);
	if (cmd->fd_in > 2)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (cmd->fd_out > 2)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	if (is_builtin(cmd->args[0]))
	{
		status = execute_builtin(cmd, minishell);
		signal(SIGINT, handle_signal);
		free_tab(env_tab);
		free_all(minishell);
		exit(status);
	}
	if (cmd->cmd_path && execve(cmd->cmd_path,
			cmd->args, env_tab) == -1)
	{
		perror("minishell");
		exit(127);
	}
	exit(0);
}

void	exec_fork(t_cmd *cmd, char **env_tab, t_minishell *minishell)
{
	pid_t pid;
	int   status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free_tab(env_tab);
		return ;
	}
	if (pid == 0)
		exe_child(cmd, minishell, env_tab);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			minishell->exit_status = WEXITSTATUS(status);
		//if (cmd->fd_in > 2)
		//	close(cmd->fd_in);
		//if (cmd->fd_out > 2)
		//	close(cmd->fd_out);
		free_tab(env_tab);
	}
}

void	wait_all_children(pid_t last_pid, t_minishell *minishell)
{
	int		status;
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	while ((pid = wait(&status)) > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				minishell->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				minishell->exit_status = 128 + WTERMSIG(status);
		}
	}
	signal(SIGINT, handle_signal);
}

void	execute_pipeline(t_minishell *minishell, t_cmd *cmd)
{
	t_list	*curr;
	int		pipe_fds[2];
	int		prev_read_fd;
	pid_t	last_pid;
	char	**env_tab;

	curr = minishell->cmds;
	prev_read_fd = -1; 
	env_tab = convert_env_to_tab(minishell->env);
	while (curr)
	{
		cmd = (t_cmd *)curr->content;
		if (curr->next && pipe(pipe_fds) == -1)
		{
			perror("pipe");
			return ;
		}
		last_pid = fork();
		if (last_pid == 0)
		{
			if (prev_read_fd != -1)
			{
				dup2(prev_read_fd, STDIN_FILENO);
				close(prev_read_fd);
			}
			if (curr->next)
			{
				close(pipe_fds[0]);
				dup2(pipe_fds[1], STDOUT_FILENO);
				close(pipe_fds[1]);
			}
			exe_child(cmd, minishell, env_tab);
		}
		if (prev_read_fd != -1)
			close(prev_read_fd);
		if (curr->next)
		{
			close(pipe_fds[1]);
			prev_read_fd = pipe_fds[0];
		}
		curr = curr->next;
		//if (cmd->fd_in > 2)
		//	close(cmd->fd_in);
		//if (cmd->fd_out > 2)
		//	close(cmd->fd_out);
	}
	free_tab(env_tab);
	wait_all_children(last_pid, minishell);
}

void	exec_command(t_minishell *minishell)
{
	t_cmd *first_cmd;

	if (!minishell->cmds)
		return ;
	first_cmd = (t_cmd *)minishell->cmds->content;
	if (ft_lstsize(minishell->cmds) == 1 && is_builtin(first_cmd->args[0]))
		builtin_status_exit(first_cmd, minishell);
	else
		execute_pipeline(minishell, first_cmd);
}
