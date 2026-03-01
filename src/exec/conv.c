/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <masenche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:59:03 by masenche          #+#    #+#             */
/*   Updated: 2026/03/01 19:14:40 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_key_value(t_env *env_node)
{
	char	*tmp;
	char	*full_string;

	tmp = ft_strjoin(env_node->key, "=");
	if (!tmp)
		return (NULL);
	full_string = ft_strjoin(tmp, env_node->value);
	free(tmp);
	return (full_string);
}

char	**convert_env_to_tab(t_list *env_list)
{
	char	**env_tab;
	int		size;
	int		i;
	t_list	*tmp;

	size = ft_lstsize(env_list);
	env_tab = malloc(sizeof(char *) * (size + 1));
	if (!env_tab)
		return (NULL);
	tmp = env_list;
	i = 0;
	while (tmp)
	{
		env_tab[i] = join_key_value((t_env *)tmp->content);
		if (!env_tab[i])
		{
			free_tab(env_tab);
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
	env_tab[i] = NULL;
	return (env_tab);
}
