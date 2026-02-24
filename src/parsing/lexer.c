/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 15:01:35 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/24 12:17:21 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_type get_type(char *token)
{
	if (ft_strcmp(token, "|") == 0)
		return (PIPE);
	if (ft_strcmp(token, "<") == 0)
		return (R_INPUT);
	if (ft_strcmp(token, ">") == 0)
		return (R_OUTPUT);
	if (ft_strcmp(token, ">>") == 0)
		return (R_OUTPUT_APPEND);
	if (ft_strcmp(token, "<<") == 0)
		return (HEREDOC);
	else
		return (WORD);
}

static void	each_token(char *prompt, int start, int *i)
{
	char	quote;
	
	quote = 0;
	while (prompt[*i])
	{
		if (quote == 0 && ft_isspace(prompt[*i]))
			break ;
		if (quote == 0 && ft_isoperator(prompt[*i]))
		{
			if (*i == start)
				(*i)++;
			if ((prompt[start] == '<' || prompt[start] == '>') && prompt[start] == prompt[*i])
				(*i)++;
			break ;
		}
		if (prompt[*i] == '\'' || prompt[*i] == '\"')
		{
			if (quote == 0)
				quote = prompt[*i];
			else if (quote == prompt[*i])
				quote = 0;
		}
		(*i)++;
	}
	return (0);
}

static t_token	*get_token(t_minishell *minishell, char *prompt, int *i)
{
	t_token	*token;
	int		start;
	
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	while (ft_isspace(prompt[*i]))
		(*i)++;
	start = *i;
	each_token(prompt, start, i);
	token->token = ft_substr(prompt, start, *i - start);
	if (!token->token)
	{
		free(token);
		return (NULL);
	}
	token->type = get_type(token->token);
	return (token);	
}

t_list	*list_token(t_minishell *minishell, char *prompt)
{
	t_list	*token_list;
	t_list	*new_node;
	t_token	*token;
	int		i;

	token_list = NULL;
	i = 0;

	while (prompt[i])
	{
		token = get_token(minishell, prompt, &i);
		if (!token)
		{
			ft_lstclear(&token_list, free_token);
			return (NULL);
		}
		new_node = ft_lstnew(token);
		if (!new_node)
		{
			free_token(token);
			ft_lstclear(&token_list, free_token);
			return (NULL);
		}
		ft_lstadd_back(&token_list, new_node);
	}

	return (token_list);
}
