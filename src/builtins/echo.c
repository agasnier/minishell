/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:48:29 by masenche          #+#    #+#             */
/*   Updated: 2026/03/09 15:41:51 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_flag_n(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] == '\0')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_echo(t_cmd *cmd)
{
	int	flag_n;
	int	i;

	flag_n = 0;
	i = 1;
	while (cmd->args[i] && is_flag_n(cmd->args[i]))
	{
		flag_n = 1;
		i++;
	}
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		i++;
		if (cmd->args[i])
			printf(" ");
	}
	if (flag_n == 0)
		printf("\n");
	return (0);
}
