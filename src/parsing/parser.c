/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:19:53 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/20 13:57:45 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	syntax_token_list(t_token *token, t_token *next)
{
	if (token->type == PIPE && (!next || next->type == PIPE))
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	if (token->type >= R_INPUT && token->type <= HEREDOC)
	{
		if (!next)
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return (1);
		}
		if (next->type != WORD)
		{
			printf("minishell: syntax error near unexpected token `%s'\n", next->token);
			return (1);
		}
	}
	return (0);
}

static int	verify_token_list(t_list *token_list)
{
	t_token	*token;
	t_token	*next_token;
	
	if (((t_token *)token_list->content)->type == PIPE)
	{
		printf("syntax error near unexpected token `|'\n");
		return (1);
	}

	while (token_list)
	{
		token = (t_token *)token_list->content;
		next_token = NULL;
		if (token_list->next)
			next_token = (t_token *)token_list->next->content;
		if (syntax_token_list(token, next_token))
			return (1);
		token_list = token_list->next; 
		
	}
	return (0);
}

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

static int	count_args(t_list *token_list)
{
	t_token	*token;
	int		args_count;

	args_count = 0;

	token = (t_token *)token_list->content;
	while (token->type == WORD)
	{
		args_count++;

		if (!token_list->next)
			break ;
		token_list = token_list->next;
		token = (t_token *)token_list->content;
	}
	return (args_count);
}

static int	format_cmds(t_minishell *minishell, t_list *token_list)
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

		args_count = count_args(token_list);
		cmd->args = malloc(sizeof(char *) * (args_count + 1));
		if (!cmd->args)
			return (1);
		
		i = 0;
		while (token_list)
		{
			token = (t_token *)token_list->content;
			if (token->type == PIPE)
			{
				token_list = token_list->next;
				break ;
			}
			else if (token->type == WORD)
			{
				cmd->args[i] = token->token;
				i++;
			}
			token_list = token_list->next;
		}
		cmd->args[i] = NULL;
		new_node = ft_lstnew(cmd);
		if (!new_node)
			return (1);
		ft_lstadd_back(&minishell->cmds, new_node);
		
	}
	return (0);
		
}

void	parsing_prompt(t_minishell *minishell, char *prompt)
{
	t_list	*token_list;
	
	token_list = list_token(prompt);

	if (!token_list)
		return ;
		
	if (verify_token_list(token_list))
	{
		minishell->exit_status = 2;
		ft_lstclear(&token_list, free_token);
		return ;
	}

	//gerer les expands ici

	//remove des quotes ici

	if (format_cmds(minishell, token_list))
		return ;

	find_path(minishell);






	
	//trouver le path de chaque commande
	//verifier infile && outfile
	//execution


	////test//////////////
	test_print_list_token(token_list);
	test_print_minish_cmds(minishell);
	/////////////////////////


	
}