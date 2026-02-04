/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:55:26 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/04 15:08:48 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_add_back(t_env **lst, t_env *new)
{
	t_env   *curr;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	curr = *lst;
	while (curr->next != NULL)
		curr = curr->next;
    
	curr->next = new;
}

void	free_env_list(t_env **env_list)
{
	t_env	*current_node;
	t_env	*next_node;

	if (!env_list || !*env_list)
		return ;
	
	current_node = *env_list;
	while (current_node)
	{
		next_node = current_node->next;
		if (current_node->key)
			free(current_node->key);
		if (current_node->value)
			free(current_node->value);

		free(current_node);
		current_node = next_node;
	}
	*env_list = NULL;
}

static int	fill_env_data(t_env *new_node, char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	new_node->key = ft_substr(str, 0, i);
	if (!new_node->key)
		return (0);
	if (str[i])
	{
		new_node->value = ft_strdup(str + i + 1);
		if (!new_node->value)
		{
			free(new_node->key);
			return (0);
		}
	}
	else
		new_node->value = NULL;
	return (1);
}

static t_env	*new_env_node(char *str)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	if (!fill_env_data(new_node, str))
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);	
}

t_env	*init_env(char **envp)
{
	t_env	*env_list;
	t_env	*new_node;
	int		i;

	env_list = NULL;

	
	if (!envp || !envp[0])
		return (NULL);

	i = 0;
	while (envp[i])
	{
		new_node = new_env_node(envp[i]);

		if (!new_node)
		{
			free_env_list(&env_list);
			return (NULL);
		}
	
		env_add_back(&env_list, new_node);
		i++;
	}
	return (env_list);
}
