/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:49:46 by masenche          #+#    #+#             */
/*   Updated: 2026/03/06 15:11:53 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "minishell.h"
#include <unistd.h>

static int is_invalid_exit_arg(const char *str)
{
	int i = 0;

	if (!str || !str[0])
		return (1);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (1);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

static void	print_exit_alph_arg(t_cmd *cmd, t_minishell *minishell)
{

	ft_printf(2, "minishell: exit: %s: numeric argument required\n", cmd->args[1]);
	free_all(minishell);
	exit(2);
}

int	builtin_exit(t_minishell *minishell, t_cmd *cmd)
{
	int	final_status;

	if (minishell->cmds && !minishell->cmds->next)
		ft_printf(2, "exit\n");
	if (cmd->args[1])
	{
		if (is_invalid_exit_arg(cmd->args[1]))
			print_exit_alph_arg(cmd, minishell);
		
		if (cmd->args[2])
		{
			ft_printf(2, "minishell: exit: too many arguments\n");
			return (1);
		}
	}
	if (!cmd->args[1])
		final_status = minishell->exit_status;
	else
		final_status = ft_atoi(cmd->args[1]);
	free_all(minishell);
	exit(final_status);
}
