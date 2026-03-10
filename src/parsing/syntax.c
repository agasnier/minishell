/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:33:05 by algasnie          #+#    #+#             */
/*   Updated: 2026/03/09 18:03:44 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	syntax_token_list(t_token *token, t_token *next)
{
	if (token->type == PIPE && (!next || next->type == PIPE))
	{
		ft_printf(2, "minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	if (token->type >= R_INPUT && token->type <= HEREDOC)
	{
		if (!next)
		{
			return (2);
		}
		if (next->type != WORD)
		{
			ft_printf(2, "minishell: syntax error near \
unexpected token `%s'\n", next->token);
			return (1);
		}
	}
	return (0);
}

static int	check_syntax(t_list *token_list)
{
	t_token	*token;
	t_token	*next_token;
	int		ret;

	if (((t_token *)token_list->content)->type == PIPE)
	{
		ft_printf(2, "minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	while (token_list)
	{
		token = (t_token *)token_list->content;
		next_token = NULL;
		if (token_list->next)
			next_token = (t_token *)token_list->next->content;
		ret = syntax_token_list(token, next_token);
		if (ret != 0)
			return (ret);
		token_list = token_list->next;
	}
	return (0);
}

int	verify_token_list(t_minishell *minishell, t_list *token_list)
{
	t_token	*token;
	t_token	*next_token;
	int		err;

	err = check_syntax(token_list);
	while (token_list)
	{
		token = (t_token *)token_list->content;
		next_token = NULL;
		if (token_list->next)
			next_token = (t_token *)token_list->next->content;
		if (token->type == HEREDOC && next_token && next_token->type == WORD)
		{
			token->heredoc_fd = handle_heredoc(minishell, next_token);
			if (token->heredoc_fd == -1)
				return (1);
		}
		token_list = token_list->next;
	}
	if (err == 2)
		ft_printf(2, "minishell: syntax error near \
unexpected token `newline'\n");
	if (err != 0)
		return (1);
	return (0);
}
