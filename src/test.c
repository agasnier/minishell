/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:23:10 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/05 12:46:29 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// print de l'init de la liste chainee
void test_print_env(t_list *env)
{
	t_env	*current;
	
	while (1)
	{
		current = (t_env *)env->content;
		printf("KEY == %s\nVALUE == %s \n\n", current->key, current->value);

		if (!env->next)
			break ;
		env = env->next;
	}
}


/// test de la recherche de la VALUE dans l'env
void test_print_env_value(t_list *env, char *key)
{
	char *value;

	value = get_env_value(env, key);
	printf("Key: %s Value: %s\n", key, value);
}



/// test du tableau des paths des exec
void	test_print_exec_path_tab(char **exec_path_tab)
{
	int	i;

	i = 0;
	while (exec_path_tab[i])
	{
		printf("%s\n", exec_path_tab[i]);
		i++;
	}


	
}