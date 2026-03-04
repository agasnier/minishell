/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:49:46 by masenche          #+#    #+#             */
/*   Updated: 2026/03/03 15:51:43 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_exit_alph_arg(t_cmd *cmd, t_minishell *minishell)
{
	int	i;

	write(1, "exit : ", 7);
	i = 0;
	while (cmd->args[1][i])
	{
		write (1, &cmd->args[1][i], 1);
		i++;
	}
	printf(": numeric argument required\n");
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
			printf("exit: too many arguments\n");
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
