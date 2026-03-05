/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:48:29 by masenche          #+#    #+#             */
/*   Updated: 2026/03/05 15:36:53 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static int	option_n(char *arg)
{
	size_t	i;

	i = 1;
	while (arg[i] == 'n')
		i++;
	if (i == ft_strlen(arg))	
		return (0);
	else
		return (-1);
}

int	builtin_echo(t_cmd *cmd)
{
	int	i;
	int	j;
	int	flag;

	if (!cmd->args[1])
	{
		printf ("\n");
		return (0);
	}
	flag = 0;
	i = 1;
	while (cmd->args[i] && option_n(cmd->args[i]) == 0)
	{
		i++;
		flag = 1;
	}
	while (cmd->args[i])
	{
		j = -1;
		while (cmd->args[i][++j])
			write(1, &cmd->args[i][j], 1);
		if (cmd->args[i + 1] != NULL)
			write (1, " ", 1);
		i++;
	}
	if (flag == 1)
		write(1, "\n", 1);
	return (0);
}
