/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:19:53 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/05 16:41:32 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing_prompt(char *prompt)
{
	t_list	*token_list;
	
	token_list = list_token(prompt);

	////test//////////////
	test_print_list_token(token_list);
	/////////////////////////


	
}