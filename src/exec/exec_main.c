/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:16:41 by masenche          #+#    #+#             */
/*   Updated: 2026/03/09 16:52:34 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


pid_t	ft_fork(t_pipeline pipeline, t_cmd *cmd,
		t_minishell *minishell, t_list *curr)
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
	t_cmd	*first_cmd;

	if (!minishell->cmds)
		return ;
	first_cmd = (t_cmd *)minishell->cmds->content;
	if (ft_lstsize(minishell->cmds) == 1
		&& is_builtin(first_cmd->args[0]))
		builtin_status_exit(first_cmd, minishell);
	else
		execute_pipeline(minishell, first_cmd);
}
