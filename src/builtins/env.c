/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:49:35 by masenche          #+#    #+#             */
/*   Updated: 2026/03/02 16:13:44 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_minishell *minishell)
{
	t_list	*current;
	t_env	*env;
	
	if (!minishell || !minishell->env)
		return (0);

	current = minishell->env;

	while (current)
	{
		env = (t_env *)current->content;
		if (env->value)
			printf("%s=%s\n", env->key, env->value);


		current = current->next;
	}	
	return (0);
}