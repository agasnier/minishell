/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 10:56:22 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/25 11:47:38 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int	state; //1 if single / 2 if double

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
int verify_unclosed_quotes(char *prompt)
{
	if (get_quote_state(prompt, ft_strlen(prompt) - 1))
	{
		printf("minishell: syntax error: unclosed quote\n");
		return (1);
	}
	return (0);
}

int	count_args(t_list *token_list)
{
	t_token	*token;
	int		args_count;

	args_count = 0;

	while (token_list)
	{
		token = (t_token *)token_list->content;
		if (token->type == PIPE)
			break ;
		else if (token->type >= R_INPUT && token->type <= HEREDOC)
		{
			if (token_list->next)
				token_list = token_list->next;
		}
		else if (token->type == WORD)
			args_count++;

		token_list = token_list->next;
	}
	return (args_count);
}