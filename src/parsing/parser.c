/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:19:53 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/25 14:41:22 by algasnie         ###   ########.fr       */
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

void	parsing_prompt(t_minishell *minishell, char *prompt)
{
	t_list	*token_list;
	
	if (verify_unclosed_quotes(prompt))
		return ;
	
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
	if (handle_expands(minishell, token_list))
		return ;
	
	remake_token_list(&token_list);

	//remove des quotes ici

	if (format_cmds(minishell, token_list))
	{
		ft_lstclear(&token_list, free_token);
		printf("minishell: memory allocation fail\n");
		return ;
	}
	ft_lstclear(&token_list, free_token);
	find_path(minishell);


	




	
	//trouver le path de chaque commande
	//verifier infile && outfile
	//execution


	////test//////////////
	//test_print_list_token(token_list);
	test_print_minish_cmds(minishell);
	/////////////////////////


	
}