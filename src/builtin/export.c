/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:49:13 by masenche          #+#    #+#             */
/*   Updated: 2026/03/02 17:05:05 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	builtin_export(t_cmd *cmd, t_minishell *minishell)
{


	if (!cmd->args[1])
		export_print_env(minishell);

	
	return (0);
}