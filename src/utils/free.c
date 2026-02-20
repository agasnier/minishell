/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 13:24:46 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/20 13:59:33 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(void *content)
{
	t_token	*token;

	if (!content)
		return ;
	token = (t_token *)content; 
	if (token->token)
		free(token->token);
	free(token);
}

void	free_env(void *content)
{
	t_env	*env;

	env = (t_env *)content;
	if (!env)
		return ;
	if (env->key)
		free(env->key);
	if (env->value)
		free(env->value);
	free(env);
}

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	free(tab);
}

void free_all(t_minishell *minishell)
{
	ft_lstclear(&minishell->env, free_env);
	free_tab(minishell->exec_path_tab);
}