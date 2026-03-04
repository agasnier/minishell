/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 14:28:53 by algasnie          #+#    #+#             */
/*   Updated: 2026/03/03 16:45:01 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_fd_out(t_cmd *cmd, t_token *token, t_token *token_next)
{
	int	fd;

	fd = 0;
	if (token->type == R_OUTPUT)
		fd = open(token_next->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (token->type == R_OUTPUT_APPEND)
		fd = open(token_next->token, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("minishell");
		return (1);
	}
	if (cmd->fd_out > 2)
		close(cmd->fd_out);
	cmd->fd_out = fd;
	return (0);
}

static int	handle_fd_in(t_cmd *cmd, t_token *token_next)
{
	int	fd;

	fd = open(token_next->token, O_RDONLY);
	if (fd == -1)
	{
		perror("minishell");
		return (1);
	}
	if (cmd->fd_in > 2)
		close(cmd->fd_in);
	cmd->fd_in = fd;
	return (0);
}

int	handle_token_type(t_cmd *cmd, t_list **token_list)
{
	t_token	*token;
	t_token	*token_next;
	
	token = (t_token *)(*token_list)->content;
	*token_list = (*token_list)->next;
	token_next = (t_token *)(*token_list)->content;

	if (token->type == R_INPUT)
	{
		if (handle_fd_in(cmd, token))
			return (1);
	}
	else if (token->type == R_OUTPUT || token->type == R_OUTPUT_APPEND)
	{
		if (handle_fd_out(cmd, token, token_next))
			return (1);
	}
	else if (token->type == HEREDOC)
	{
		
	}
	return (0);
}
