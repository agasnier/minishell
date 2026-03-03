/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:49:27 by masenche          #+#    #+#             */
/*   Updated: 2026/03/03 16:31:41 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_env_var(t_list **env_list, char *key)
{
	t_list	*prev;
	t_list	*current;
	t_env	*env_node;

	current = *env_list;
	prev = NULL;
	while (current)
	{
		env_node = (t_env *)current->content;
		if (ft_strcmp(env_node->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env_list = current->next;
			free_env(env_node);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	builtin_unset(t_cmd *cmd, t_minishell *minishell)
{
	int		i;

	if (!cmd->args[1])
		return (0);
	i = 1;
	while (cmd->args[i])
	{
		remove_env_var(&minishell->env, cmd->args[i]);
		i++;
	}
	return (0);
}
