/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:11:35 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/05 11:59:59 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_env_value(t_list *env, char *key)
{
	t_env	*current;

	while (env)
	{
		current = (t_env *)env->content;
		
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		env = env->next;
	}
	return (NULL);
}