/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 09:16:51 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/24 09:43:05 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int is_there_expands(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	handle_expands(t_list *token_list)
{
	t_token	*token;

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