/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:19:53 by algasnie          #+#    #+#             */
/*   Updated: 2026/03/10 10:29:49 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	command_builder_part(t_minishell *minishell, t_list *token_list)
{
	if (format_cmds(minishell, token_list))
	{
		ft_lstclear(&token_list, free_token);
		minishell->token_list = NULL;
		ft_lstclear(&minishell->cmds, free_cmds);
		minishell->exit_status = 1;
		return (1);
	}
	ft_lstclear(&token_list, free_token);
	minishell->token_list = NULL;
	find_path(minishell);
	return (0);
}

static int	expands_part(t_minishell *minishell, t_list **token_list)
{
	if (handle_expands(minishell, *token_list))
	{
		minishell->exit_status = 1;
		return (1);
	}
	if (remake_token_list(token_list))
	{
		minishell->exit_status = 1;
		return (1);
	}
	return (0);
}

static int	validation_part(t_minishell *minishell, t_list *token_list)
{
	if (verify_token_list(minishell, token_list))
	{
		minishell->exit_status = 2;
		ft_lstclear(&token_list, free_token);
		return (1);
	}
	return (0);
}

static int	lexing_part(t_minishell *minishell,
	char *prompt, t_list **token_list)
{
	if (verify_unclosed_quotes(prompt))
	{
		minishell->exit_status = 2;
		return (1);
	}
	*token_list = list_token(prompt);
	if (!(*token_list))
		return (1);
	return (0);
}

void	parsing_prompt(t_minishell *minishell, char *prompt)
{
	if (minishell->exec_path_tab)
		free_tab(minishell->exec_path_tab);
	minishell->exec_path_tab = get_exec_path(minishell);
	if (lexing_part(minishell, prompt, &minishell->token_list))
	{
		ft_lstclear(&minishell->cmds, free_cmds);
		return ;
	}
	if (validation_part(minishell, minishell->token_list))
	{
		ft_lstclear(&minishell->cmds, free_cmds);
		return ;
	}
	if (expands_part(minishell, &minishell->token_list))
	{
		ft_lstclear(&minishell->cmds, free_cmds);
		return ;
	}
	if (command_builder_part(minishell, minishell->token_list))
		return ;
}
