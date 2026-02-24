/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 10:56:22 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/24 12:11:20 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_quote_state(char *str, int index)
{
	int	i;
	int	state; //1 if single / 2 if double

	if (!str || index < 0)
		return (0);

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
int verify_unclosed_quotes(char *prompt)
{
	if (get_quote_state(prompt, ft_strlen(prompt) - 1))
	{
		printf("minishell: syntax error: unclosed quote\n");
		return (1);
	}
	return (0);
}