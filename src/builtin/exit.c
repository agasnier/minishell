/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:49:46 by masenche          #+#    #+#             */
/*   Updated: 2026/03/02 17:46:46 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_exit(t_minishell *minishell)
{
	int final_status;

    ft_putstr_fd("exit\n", 2);
    final_status = minishell->exit_status;
	free_all(minishell);
    exit(final_status);
}