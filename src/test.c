/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:23:10 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/04 18:45:47 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// print de l'init de la liste chainee
void test_print_env(t_list *env)
{
	t_list	*current;
	
	current = env;
	while (1)
	{
		printf("KEY == %s\nVALUE == %s \n\n", current->content, current->value);

		if (!current->next)
			break ;
		current = current->next;
	}
}


/// test de la recherche de la VALUE dans l'env
// void test_print_env_value(t_env *env, char *key)
// {
// 	char *value;

// 	value = get_env_value(env, key);
// 	printf("Key: %s Value: %s\n", key, value);
// }