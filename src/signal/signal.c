/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 18:45:32 by masenche          #+#    #+#             */
/*   Updated: 2026/03/09 16:49:06 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_receive_message = 0;

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_receive_message = SIGINT;
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGQUIT)
		rl_redisplay();
}
