/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:49:46 by masenche          #+#    #+#             */
/*   Updated: 2026/03/06 13:53:20 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_exit_alph_arg(t_cmd *cmd, t_minishell *minishell)
{
	int	i;

	write(1, "exit : ", 7);
	i = 0;
	while (cmd->args[1][i])
	{
		write (1, &cmd->args[1][i], 1);
		i++;
	}
	ft_printf(2, "minishell: numeric argument required\n");
	free_all(minishell);
	exit(2);
}

int	builtin_exit(t_minishell *minishell, t_cmd *cmd)
{
	int	final_status;
	int	i;

	ft_putstr_fd("exit\n", 2);
	if (cmd->args[1])
	{
		if (cmd->args[2])
		{
			ft_printf(2, "minishell: exit: too many arguments\n");
			return (1);
		}
		i = 0;
		while (cmd->args[1][i])
		{
			if (ft_isalpha(cmd->args[1][i]) == 1)
			print_exit_alph_arg(cmd, minishell);
		i++;
		}
	}
	if (!cmd->args[1])
		final_status = minishell->exit_status;
	else
		final_status = ft_atoi(cmd->args[1]);
	free_all(minishell);
	exit(final_status);
}
