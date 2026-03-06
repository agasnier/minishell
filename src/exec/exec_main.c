/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:16:41 by masenche          #+#    #+#             */
/*   Updated: 2026/03/06 13:36:21 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

static void	exe_child_fd(t_cmd *cmd)
{
	if (cmd->fd_in != -1)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (cmd->fd_out != -1)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
}

void	exe_child(t_cmd *cmd, t_minishell *minishell, char **env_tab)
{
	int status;

	exe_child_fd(cmd);

	signal(SIGINT, SIG_DFL);
	if (is_builtin(cmd->args[0]))
	{
		status = execute_builtin(cmd, minishell);
		signal(SIGINT, handle_signal);
		free_tab(env_tab);
		free_all(minishell);
		exit(status);
	}
	if (!cmd->cmd_path)
	{
		ft_printf(2, "minishell: %s: command not found\n", cmd->args[0]);
		free_tab(env_tab);
		free_all(minishell);
		exit (127);
	}
	execve(cmd->cmd_path, cmd->args, env_tab);
	ft_printf(2, "minishell: ");
	perror(cmd->args[0]);
	free_tab(env_tab);
	free_all(minishell);
	exit(126);

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

pid_t	ft_fork(t_pipeline pipeline, t_cmd *cmd, t_minishell *minishell, t_list *curr)
{
	pid_t	last_pid;

	last_pid = fork();
	if (last_pid == 0)
	{
		close_fd(pipeline.prev_read_fd, curr, pipeline.pipe_fds);
		exe_child(cmd, minishell, pipeline.env_tab);
	}
	if (pipeline.prev_read_fd != -1)
		close(pipeline.prev_read_fd);
	return (last_pid);
}

void	execute_pipeline(t_minishell *minishell, t_cmd *cmd)
{
	t_list		*curr;
	t_pipeline	pipeline;
	pid_t		last_pid;

	pipeline.env_tab = convert_env_to_tab(minishell->env);
	pipeline.prev_read_fd = -1;
	curr = minishell->cmds;
	while (curr)
	{
		cmd = (t_cmd *)curr->content;
		if (curr->next && pipe(pipeline.pipe_fds) == -1)
		{
			perror("pipe");
			return ;
		}
		last_pid = ft_fork(pipeline, cmd, minishell, curr);
		if (curr->next)
			pipeline.prev_read_fd = close_read_fd(pipeline.pipe_fds);
		curr = curr->next;
	}
	free_tab(pipeline.env_tab);
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
