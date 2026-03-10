/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_expands_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:40:34 by algasnie          #+#    #+#             */
/*   Updated: 2026/03/10 14:23:48 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	sub_token(t_list **current, char *content)
{
	t_token	*new_token;
	t_list	*new_node;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (1);
	new_token->token = ft_strdup(content);
	if (!new_token->token)
	{
		free(new_token);
		return (1);
	}
	new_token->type = WORD;
	new_token->quoted = 0;
	new_node = ft_lstnew(new_token);
	new_token->heredoc_fd = 0;
	if (!new_node)
	{
		free_token(new_token);
		return (1);
	}
	new_node->next = (*current)->next;
	(*current)->next = new_node;
	*current = new_node;
	return (0);
}

static int	word_split_helper(t_list **current, char **tokens)
{
	int	i;

	i = 1;
	while (tokens[i])
	{
		if (sub_token(current, tokens[i]))
		{
			free_tab(tokens);
			return (1);
		}
		i++;
	}
	return (0);
}

int	word_split(t_list **current)
{
	t_token	*token;
	char	**tokens;

	token = (t_token *)(*current)->content;
	tokens = ft_split_unquoted(token->token, ' ');
	if (!tokens)
		return (1);
	if (tokens[0])
	{
		free (token->token);
		token->token = ft_strdup(tokens[0]);
		if (!token->token)
		{
			free_tab(tokens);
			return (1);
		}
		if (word_split_helper(current, tokens))
			return (1);
	}
	free_tab(tokens);
	return (0);
}
