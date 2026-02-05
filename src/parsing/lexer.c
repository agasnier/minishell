/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 15:01:35 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/05 16:26:12 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_token(char *prompt, int *i)
{
	char	*token;
	int		start;
	
	while (ft_isspace(prompt[*i]))
		(*i)++;
	start = *i;
	while (prompt[*i] && !isspace(prompt[*i]))
		(*i)++;
	token = ft_substr(prompt, start, *i - start);
	//////////////////gerer le '\0' et le NULL
	return (token);	
}

t_list	*list_token(char *prompt)
{
	t_list	*token_list;
	t_list	*new_node;
	char	*token;
	int		i;

	token_list = NULL;
	i = 0;

	while (prompt[i])
	{
		token = get_token(prompt, &i);
		//////////////////////gerer le NULL
		new_node = ft_lstnew(token);
		ft_lstadd_back(&token_list, new_node);
		i++;
	}

	return (token_list);
}