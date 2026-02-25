/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:40:53 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/25 14:54:28 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd *init_cmd_struct(void)
{	
	t_cmd *cmd;
	
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->cmd_path = NULL;
	cmd->fd_in = -1;
	cmd->fd_out = -1;
	return (cmd);
}

int	format_cmds(t_minishell *minishell, t_list *token_list)
{
	t_cmd	*cmd;
	t_token	*token;
	int		args_count;
	t_list	*new_node;
	int		i;
	
	

	minishell->cmds = NULL;

	while (token_list)
	{
		cmd = init_cmd_struct();
		if (!cmd)
			return (1);

		args_count = count_args_list(token_list);
		cmd->args = malloc(sizeof(char *) * (args_count + 1));
		if (!cmd->args)
		{
			free(cmd);
			return (1);
		}
		
		i = 0;
		while (token_list)
		{
			token = (t_token *)token_list->content;
			if (token->type == PIPE)
			{
				token_list = token_list->next;
				break ;
			}
			else if (token->type >= R_INPUT && token->type <= HEREDOC)
			{
				if (token_list->next)
					token_list = token_list->next;
			}
			else if (token->type == WORD)
			{
				cmd->args[i] = ft_strdup(token->token);
				if (!cmd->args[i])
				{
					free_tab(cmd->args);
					free(cmd);
					return (1);
				}
					
				i++;
			}
			token_list = token_list->next;
		}
		cmd->args[i] = NULL;
		new_node = ft_lstnew(cmd);
		if (!new_node)
		{
			free(cmd->args);
			free(cmd);
			return (1);
		}
		ft_lstadd_back(&minishell->cmds, new_node);
		
	}
	return (0);
		
}