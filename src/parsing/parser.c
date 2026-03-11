/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:19:53 by algasnie          #+#    #+#             */
/*   Updated: 2026/03/11 15:36:22 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	command_builder_part(t_minishell *minishell)
{
	if (format_cmds(minishell, minishell->token_list))
	{
		ft_lstclear(&minishell->token_list, free_token);
		minishell->token_list = NULL;
		ft_lstclear(&minishell->cmds, free_cmds);
		minishell->exit_status = 1;
		return (1);
	}
	ft_lstclear(&minishell->token_list, free_token);
	minishell->token_list = NULL;
	find_path(minishell);
	return (0);
}

static int	expands_part(t_minishell *minishell)
{
	if (handle_expands(minishell, minishell->token_list))
	{
		minishell->exit_status = 1;
		return (1);
	}
	if (remake_token_list(&minishell->token_list))
	{
		minishell->exit_status = 1;
		ft_lstclear(&minishell->token_list, free_token);
		return (1);
	}
	return (0);
}

static int	validation_part(t_minishell *minishell)
{
	if (verify_token_list(minishell, minishell->token_list))
	{
		minishell->exit_status = 2;
		ft_lstclear(&minishell->token_list, free_token);
		return (1);
	}
	return (0);
}

static int	lexing_part(t_minishell *minishell, char *prompt)
{
	if (verify_unclosed_quotes(prompt))
	{
		minishell->exit_status = 2;
		return (1);
	}
	minishell->token_list = list_token(prompt);
	if (!(minishell->token_list))
		return (1);
	return (0);
}

void	parsing_prompt(t_minishell *minishell, char *prompt)
{
	if (minishell->exec_path_tab)
		free_tab(minishell->exec_path_tab);
	minishell->exec_path_tab = get_exec_path(minishell);
	if (lexing_part(minishell, prompt))
	{
		ft_lstclear(&minishell->cmds, free_cmds);
		return ;
	}
	if (validation_part(minishell))
	{
		ft_lstclear(&minishell->cmds, free_cmds);
		return ;
	}
	if (expands_part(minishell))
	{
		ft_lstclear(&minishell->cmds, free_cmds);
		return ;
	}
	if (command_builder_part(minishell))
		return ;
}
