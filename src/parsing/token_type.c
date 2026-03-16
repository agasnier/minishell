/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 14:28:53 by algasnie          #+#    #+#             */
/*   Updated: 2026/03/16 15:57:10 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_fd_out(t_minishell *minishell,
	t_cmd *cmd, t_token *token, t_token *token_next)
{
	int	fd;

	if (cmd->fd_out == -2)
		return (0);
	if (token_next->heredoc_fd == -1)
	{
		cmd->fd_out = -2;
		return (0);
	}
	fd = 0;
	if (token->type == R_OUTPUT)
		fd = open(token_next->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (token->type == R_OUTPUT_APPEND)
		fd = open(token_next->token, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_printf(STDERR_FILENO, "minishell: %s: %s\n",
			token_next->token, strerror(errno));
		minishell->exit_status = 1;
		fd = -2;
	}
	if (cmd->fd_out > 2)
		close(cmd->fd_out);
	cmd->fd_out = fd;
	return (0);
}

static int	handle_fd_in(t_minishell *minishell,
	t_cmd *cmd, t_token *token_next)
{
	int	fd;

	if (cmd->fd_in == -2)
		return (0);
	if (token_next->heredoc_fd == -1)
	{
		cmd->fd_out = -2;
		return (0);
	}
	fd = open(token_next->token, O_RDONLY);
	if (fd == -1)
	{
		ft_printf(STDERR_FILENO, "minishell: %s: %s\n",
			token_next->token, strerror(errno));
		fd = -2;
		minishell->exit_status = 1;
	}
	if (cmd->fd_in > 2)
		close(cmd->fd_in);
	cmd->fd_in = fd;
	return (0);
}

static int	handle_token_type_helper(t_minishell *minishell, t_cmd *cmd, t_token *token, t_token *token_next)
{
		if (token->type == R_INPUT)
	{
		if (handle_fd_in(minishell, cmd, token_next))
			return (1);
	}
	else if (token->type == R_OUTPUT || token->type == R_OUTPUT_APPEND)
	{
		if (handle_fd_out(minishell, cmd, token, token_next))
			return (1);
	}
	return (0);
}

static void	handle_ambiguous(t_minishell *minishell, t_cmd *cmd, t_token *token)
{
	ft_printf(STDERR_FILENO, "minishell: ambiguous redirect\n");
	minishell->exit_status = 1;
	if (token->type == R_INPUT || token->type == HEREDOC)
		cmd->fd_in = -2;
	else
		cmd->fd_out = -2;
}

int	handle_token_type(t_minishell *minishell, t_cmd *cmd, t_list **token_list)
{
	t_token	*token;
	t_token	*token_next;

	token = (t_token *)(*token_list)->content;
	*token_list = (*token_list)->next;
	if (!(*token_list) || ((t_token *)(*token_list)->content)->type != WORD)
	{
		handle_ambiguous(minishell, cmd, token);
		return (0);
	}
	token_next = (t_token *)(*token_list)->content;
	if ((token->type == R_INPUT) || (token->type == R_OUTPUT || token->type == R_OUTPUT_APPEND))
	{
		if (handle_token_type_helper(minishell, cmd, token, token_next))
			return (1);
	}
	else if (token->type == HEREDOC)
	{
		cmd->delim_quoted = token_next->quoted;
		if (cmd->fd_in > 2)
			close(cmd->fd_in);
		cmd->fd_in = token->heredoc_fd;
		token->heredoc_fd = -2;
	}
	return (0);
}
