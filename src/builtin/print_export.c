/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 17:05:06 by algasnie          #+#    #+#             */
/*   Updated: 2026/03/03 10:12:18 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void print_export(t_env **tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (tab[i]->exported)
		{
			printf("declare -x %s", tab[i]->key);
			if (tab[i]->value)
				printf("=\"%s\"", tab[i]->value);
			printf("\n");
		}
		i++;
	}
}

static void	sort_env_tab(t_env **tab, int size)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(tab[j]->key, tab[j + 1]->key) > 0)
			{
				tmp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	
}

static void	fill_sorted_env(t_list *env_list, t_env **sorted_env)
{
	int	i;

	i = 0;
	while (env_list)
	{
		sorted_env[i] = (t_env *)env_list->content;
		env_list = env_list->next;
		i++;
	}
}


int	export_print_env(t_minishell *minishell)
{
	int		size;
	t_env	**sorted_env;

	size = ft_lstsize(minishell->env);
	sorted_env = malloc(sizeof(t_env *) * size);
	if (!sorted_env)
		return (1);

	fill_sorted_env(minishell->env, sorted_env);
	sort_env_tab(sorted_env, size);
	print_export(sorted_env, size);
	free(sorted_env);
	return (0);
}