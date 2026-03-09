/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:49:46 by masenche          #+#    #+#             */
/*   Updated: 2026/03/09 17:54:18 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_invalid_exit_arg(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (1);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (1);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			while(str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
				i++;
			if (str[i])
				return (1);
			return (0);
		}
		i++;
	}
	return (0);
}

static void	print_exit_alph_arg(t_cmd *cmd, t_minishell *minishell)
{
	ft_printf(2, "minishell: exit: %s: numeric argument required\n",
		cmd->args[1]);
	free_all(minishell);
	exit(2);
}

int	builtin_exit(t_minishell *minishell, t_cmd *cmd)
{
	int			error_flag;
	long long	res;

	if (minishell->cmds && !minishell->cmds->next)
		ft_printf(2, "exit\n");
	if (!cmd->args[1])
    {
        free_all(minishell);
        exit(minishell->exit_status);
    }
	error_flag = 0;
	res = ft_atoll_check(cmd->args[1], &error_flag);
	if (is_invalid_exit_arg(cmd->args[1]) || error_flag)
		print_exit_alph_arg(cmd, minishell);
	if (cmd->args[2])
	{
		ft_printf(2, "minishell: exit: too many arguments\n");
		return (1);
	}
	free_all(minishell);
	exit((unsigned char)res);
}
