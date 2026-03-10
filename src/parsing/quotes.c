/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:34:28 by algasnie          #+#    #+#             */
/*   Updated: 2026/03/09 17:30:39 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_len_unquoted(char *str)
{
	int	i;
	int	state;
	int	old_state;
	int	len;

	i = 0;
	len = 0;
	state = 0;
	while (str && str[i])
	{
		old_state = state;
		update_quote_state(str[i], &state);
		if (state == old_state)
			len++;
		i++;
	}
	return (len);
}

char	*remove_token_quotes(char *str)
{
	int		i;
	int		j;
	int		state;
	int		old_state;
	char	*new_str;

	i = 0;
	j = 0;
	state = 0;
	new_str = malloc(sizeof(char) * (get_len_unquoted(str) + 1));
	if (!new_str)
		return (NULL);
	while (str && str[i])
	{
		old_state = state;
		update_quote_state(str[i], &state);
		if (state == old_state)
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

void	update_quote_state(char c, int *state)
{
	if (c == '\'' && *state == 0)
		*state = 1;
	else if (c == '\'' && *state == 1)
		*state = 0;
	else if (c == '\"' && *state == 0)
		*state = 2;
	else if (c == '\"' && *state == 2)
		*state = 0;
}

int	get_quote_state(char *str, int index)
{
	int	i;
	int	state;

	if (!str || index < 0)
		return (0);
	i = 0;
	state = 0;
	while (str[i] && i <= index)
	{
		update_quote_state(str[i], &state);
		i++;
	}
	return (state);
}

int	verify_unclosed_quotes(char *prompt)
{
	if (get_quote_state(prompt, ft_strlen(prompt) - 1))
	{
		ft_printf(2, "minishell: syntax error: unclosed quote\n");
		return (1);
	}
	return (0);
}
