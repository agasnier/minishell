/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:48:29 by masenche          #+#    #+#             */
/*   Updated: 2026/03/02 16:52:41 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 1;
	if (ft_strcmp(cmd->args[1], "-n") == 0)
		i = 2;
	while (cmd->args[i])
	{
		j = 0;
		while (cmd->args[i][j])
		{
			write(1, &cmd->args[i][j], 1);
			j++;
		}
		i++;
	}
	if (ft_strcmp(cmd->args[1], "-n"))
		write(1, "\n", 1);
	return (0);
}
