/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:19:53 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/06 11:07:56 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing_prompt(char *prompt)
{
	t_list	*token_list;
	
	///lexer --> token WORD OPERATOR ETC
	token_list = list_token(prompt);
	////test//////////////
	test_print_list_token(token_list);
	/////////////////////////
	
	//parser
	//verifier la coherence
	//creation structure **cmd / path / infile / outfile --> PIPEX
	//mettre les cmds et args dans struct
	//trouver le path de chaque commande
	//verifier infile && outfile
	//execution



	
}