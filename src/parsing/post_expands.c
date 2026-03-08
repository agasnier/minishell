/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_expands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 11:14:26 by algasnie          #+#    #+#             */
/*   Updated: 2026/03/08 20:21:13 by algasnie         ###   ########.fr       */
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

static int word_split(t_list **current)
{
	t_token	*token;
	char	**tokens;
	int		i;


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
	}
	free_tab(tokens);
	return (0);
}

int remake_token_list(t_list **token_list)
{
	t_list	*current;
	t_list	*prev;
	t_list	*tmp;
	t_token	*token;

	current = *token_list;
	prev = NULL;
	
	while (current)
	{
		token = (t_token *)current->content;
		if (!token->token || token->token[0] == '\0')
		{
			tmp = current;
			current = current->next;
			if (prev)
				prev->next = current;
			else
				*token_list = current;
			ft_lstdelone(tmp, free_token);
			continue ;
		}
		if (word_split(&current))
			return 1;
		prev = current;
		current = current->next;
	}
	if (remove_quotes(token_list))
		return (1);
	return (0);
}
