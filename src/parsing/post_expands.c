/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_expands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 11:14:26 by algasnie          #+#    #+#             */
/*   Updated: 2026/03/09 15:40:15 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	remove_quotes(t_list **token_list)
{
	t_list	*current;
	t_token	*token;

	current = *token_list;
	while (current)
	{
		token = (t_token *)current->content;
		if (token->type == WORD)
		{
			token->token = remove_token_quotes(token->token);
			if (!token->token)
				return (1);
		}
		current = current->next;
	}
	return (0);
}

static void	delanode(t_list **token_list, t_list *prev, t_list **current)
{
	t_list	*tmp;

	tmp = *current;
	*current = (*current)->next;
	if (prev)
		prev->next = *current;
	else
		*token_list = *current;
	ft_lstdelone(tmp, free_token);
}

int	remake_token_list(t_list **token_list)
{
	t_list	*current;
	t_list	*prev;
	t_token	*token;

	current = *token_list;
	prev = NULL;
	while (current)
	{
		token = (t_token *)current->content;
		if (!token->token || token->token[0] == '\0')
		{
			delanode(token_list, prev, &current);
			continue ;
		}
		if (word_split(&current))
			return (1);
		prev = current;
		current = current->next;
	}
	if (remove_quotes(token_list))
		return (1);
	return (0);
}
