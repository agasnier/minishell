/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:53:28 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/05 12:24:56 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_exec_path(t_minishell *minishell)
{
	char	*path;
	char	**tab_path;
	t_list	*path_list;
	t_list	*new_node;
	

	path = get_env_value(minishell->env, "PATH");
	if (!path)
		return (NULL);

	tab_path = ft_split(path, ':');
	if (!tab_path)
		return (NULL);
	
	int i = 0;
	
	while (tab_path[i])
	{
		new_node = ft_lstnew(tab_path[i]);
		ft_lstadd_back(&path_list, new_node);
		i++;
	}
	
	return (path_list);

}