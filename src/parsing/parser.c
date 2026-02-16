/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:19:53 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/16 17:23:52 by algasnie         ###   ########.fr       */
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
	//mettre les cmds et args dans struct
	//trouver le path de chaque commande
	//verifier infile && outfile
	//execution



	
}