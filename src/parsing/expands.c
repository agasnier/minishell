/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 09:16:51 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/24 10:46:57 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



static int is_there_expands(char *word)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (word[i])
	{
		if (word[i] == '\'')
		{
			if (single_quote == 0)
				single_quote = 1;
			else
				single_quote = 0;
		}
		if (word[i] == '$' && single_quote != 1)
			return (1);
		i++;
	}
	return (0);
}

int	handle_expands(t_minishell *minishell, t_list *token_list)
{
	t_token	*token;

	(void)minishell;

	while(token_list)
	{
		token = (t_token *)token_list->content;
		
		if (is_there_expands(token->token))
		{
			
			printf("\nexpand: %s\n", token->token);
		}
		


		token_list = token_list->next;
	}


	return (0);
}