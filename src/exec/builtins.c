/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:47:55 by masenche          #+#    #+#             */
/*   Updated: 2026/03/06 15:09:14 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	execute_builtin(t_cmd *cmd, t_minishell *minishell)
{
	int	builtin_status;

	if (!cmd->args[0])
		return (1);
	builtin_status = 0;
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		builtin_status = builtin_echo(cmd);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		builtin_status = builtin_cd(cmd, minishell);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		builtin_status = builtin_pwd(cmd);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		builtin_status = builtin_export(cmd, minishell);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		builtin_status = builtin_unset(cmd, minishell);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		builtin_status = builtin_env(minishell);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		builtin_status = builtin_exit(minishell, cmd);
	return (builtin_status);
}

void	builtin_status_exit(t_cmd *cmd, t_minishell *minishell)
{
    int saved_fds[2];

    if (ft_strcmp(cmd->args[0], "exit") == 0)
	{
		minishell->exit_status = builtin_exit(minishell, cmd);
		return ;
	}
	saved_fds[0] = dup(STDIN_FILENO);
    saved_fds[1] = dup(STDOUT_FILENO);
    if (saved_fds[0] == -1 || saved_fds[1] == -1)
		return ;
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
    minishell->exit_status = execute_builtin(cmd, minishell);
    dup2(saved_fds[0], STDIN_FILENO);
    dup2(saved_fds[1], STDOUT_FILENO);
    close(saved_fds[0]);
    close(saved_fds[1]);
}
