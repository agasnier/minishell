/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:19:53 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/17 10:37:59 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	verify_token_list(t_list *token_list)
{
	t_token	*token;

	token = (t_token *)token_list->content;

	if (token->type == PIPE)
	{
		printf("syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}

static t_cmd *init_cmd_struct(void)
{
	t_cmd	*cmd;
	
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
	
	
	cmd = init_cmd_struct();
	if (!cmd)
		return (1);
	(void)minishell->cmds;
	token = (t_token *)token_list->content;
	
	args_count = count_args(token_list);
	
	while (token->type == WORD)
	{
		printf("token= %s count= %d\n", token->token, args_count);

		if (!token_list->next)
			break ;
		token_list = token_list->next;
		token = (t_token *)token_list->content;
	}

	return (0);
	

	

	
}

void	parsing_prompt(t_minishell *minishell, char *prompt)
{
	t_list	*token_list;
	
	///lexer --> token WORD OPERATOR ETC
	token_list = list_token(prompt);
	////test//////////////
	test_print_list_token(token_list);
	/////////////////////////
	
	
	//parser
	
	// cat << EOF
	// | at start
	
	verify_token_list(token_list);
	
	//verifier la coherence
	//creation structure **cmd / path / infile / outfile --> PIPEX

	format_cmds(minishell, token_list); ///if return 1;

	//mettre les cmds et args dans struct
	//trouver le path de chaque commande
	//verifier infile && outfile
	//execution



	
}