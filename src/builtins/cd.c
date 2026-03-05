/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:48:54 by masenche          #+#    #+#             */
/*   Updated: 2026/03/03 14:29:08 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(t_cmd *cmd, t_minishell *minishell)
{
	char	*target_dir;
	char	cwd[1024];

	if (cmd->args[1] == NULL)
		target_dir = get_env_value(minishell, "HOME");
	else
		target_dir = cmd->args[1];
	if (!target_dir)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	if (chdir(target_dir) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		update_env_value(minishell, "PWD", cwd);
	else
		perror("minishell: cd: getcwd failed");
	return (0);
}
