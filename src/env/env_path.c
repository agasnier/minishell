/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <masenche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:53:28 by algasnie          #+#    #+#             */
/*   Updated: 2026/03/01 19:15:31 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_exec_path(t_minishell *minishell)
{
	char	*path;
	char	**path_tab;

	path = get_env_value(minishell, "PATH");
	if (!path)
		return (NULL);
	path_tab = ft_split(path, ':');
	if (!path_tab)
		return (NULL);
	free(path);
	return (path_tab);
}

void	update_env_value(t_minishell *minishell, char *key, char *new_value)
{
	t_list	*tmp;
	t_env	*env_node;
	t_list	*new_node;

	tmp = minishell->env;
	while (tmp)
	{
		env_node = (t_env *)tmp->content;
		if (ft_strcmp(env_node->key, key) == 0)
		{
			free(env_node->value);
			env_node->value = ft_strdup(new_value);
			return ;
		}
		tmp = tmp->next;
	}
	env_node = malloc(sizeof(t_env));
	if (!env_node)
		return ;
	env_node->key = ft_strdup(key);
	env_node->value = ft_strdup(new_value);
	env_node->exported = 1;
	new_node = ft_lstnew(env_node);
	if (!env_node->key || !new_node)
	{
		free_env(env_node);
		return ;
	}
	ft_lstadd_back(&minishell->env, new_node);
}
