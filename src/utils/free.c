/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 13:24:46 by algasnie          #+#    #+#             */
/*   Updated: 2026/03/10 10:23:07 by algasnie         ###   ########.fr       */
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
	if (token->heredoc_fd > 2)
		close(token->heredoc_fd);
	free(token);
}

void	free_cmds(void *content)
{
	t_cmd	*cmd;

	if (!content)
		return ;
	cmd = (t_cmd *)content;
	if (cmd->fd_in > 2)
		close(cmd->fd_in);
	if (cmd->fd_out > 2)
		close(cmd->fd_out);
	if (cmd->args)
		free_tab(cmd->args);
	if (cmd->cmd_path)
		free(cmd->cmd_path);
	free(cmd);
}

void	free_env(void *content)
{
	t_env	*env;

	if (!content)
		return ;
	env = (t_env *)content;
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

void	free_all(t_minishell *minishell)
{
	if (minishell->env)
		ft_lstclear(&minishell->env, free_env);
	if (minishell->exec_path_tab)
		free_tab(minishell->exec_path_tab);
	if (minishell->cmds)
		ft_lstclear(&minishell->cmds, free_cmds);
	if (minishell->token_list)
	{
		ft_lstclear(&(minishell->token_list), free_token);
		minishell->token_list = NULL;
	}
}
