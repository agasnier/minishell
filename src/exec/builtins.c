/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:47:55 by masenche          #+#    #+#             */
/*   Updated: 2026/03/02 18:28:44 by masenche         ###   ########.fr       */
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
	if (ft_strcmp(cmd->args[0], "echo") == 0)
	{
		builtin_status = builtin_echo(cmd);
		return (builtin_status);
	}
	if (ft_strcmp(cmd->args[0], "cd") == 0)
	{
		builtin_status = builtin_cd(cmd, minishell);
		return (builtin_status);
	}
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
	{
		builtin_status = builtin_pwd(cmd);
		return (builtin_status);
	}
	if (ft_strcmp(cmd->args[0], "export") == 0)
	{
		builtin_status = builtin_export(cmd, minishell);
		return (builtin_status);
	}
	if (ft_strcmp(cmd->args[0], "unset") == 0)
	{
		builtin_status = builtin_unset(cmd, minishell);
		return (builtin_status);
	}
	if (ft_strcmp(cmd->args[0], "env") == 0)
	{
		builtin_status = builtin_env(cmd, minishell);
		return (builtin_status);
	}
	return (1);
}

void    builtin_status_exit(t_cmd *cmd, t_minishell *minishell)
{
    int saved_fds[2];

    if (ft_strcmp(cmd->args[0], "exit") == 0)
        builtin_exit(minishell);
    saved_fds[0] = dup(STDIN_FILENO);
    saved_fds[1] = dup(STDOUT_FILENO);
    if (saved_fds[0] == -1 || saved_fds[1] == -1)
        return ;
    //if (cmd->fd_in > 2)
    //    dup2(cmd->fd_in, STDIN_FILENO);
    //if (cmd->fd_out > 2)
    //    dup2(cmd->fd_out, STDOUT_FILENO);
    minishell->exit_status = execute_builtin(cmd, minishell);
    dup2(saved_fds[0], STDIN_FILENO);
    dup2(saved_fds[1], STDOUT_FILENO);
    close(saved_fds[0]);
    close(saved_fds[1]);
}
