/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 15:01:35 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/05 18:11:29 by algasnie         ###   ########.fr       */
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

static t_token	*get_token(char *prompt, int *i)
{
	t_token	*token;
	int		start;
	
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	while (ft_isspace(prompt[*i]))
		(*i)++;
	start = *i;
	while (prompt[*i] && !isspace(prompt[*i]))
		(*i)++;
	token->token = ft_substr(prompt, start, *i - start);
	//////////////////gerer le '\0' et le NULL
	token->type = get_type(token->token);
	return (token);	
}

t_list	*list_token(char *prompt)
{
	t_list	*token_list;
	t_list	*new_node;
	t_token	*token;
	int		i;

	token_list = NULL;
	i = 0;

	while (prompt[i])
	{
		token = get_token(prompt, &i);
		//////////////////////gerer le NULL
		new_node = ft_lstnew(token);
		ft_lstadd_back(&token_list, new_node);
		i++;
	}

	return (token_list);
}