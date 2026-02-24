/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 10:56:22 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/24 10:59:54 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_quote_state(char *str, int index)
{
	int	i;
	int	state; //1 if single / 2 if double

	i = 0;
	state = 0;
	while (str[i] && i <= index)
	{
		if (str[i] == '\'' && state == 0)
			state = 1;
		else if (str[i] == '\'' && state == 1)
			state = 0;
		else if (str[i] == '\"' && state == 0)
			state = 2;
		else if (str[i] == '\"' && state == 2)
			state = 0;
		i++;
	}
	return (state);
}