/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 16:25:35 by algasnie          #+#    #+#             */
/*   Updated: 2026/03/10 13:48:38 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_absolute_path(char **cmd)
{
	char	*ret;

	if (access(cmd[0], X_OK) == 0)
	{
		ret = ft_strdup(cmd[0]);
		return (ret);
	}
	return (NULL);
}

static char	*find_exec(t_minishell *minishell, char **cmd, char **path)
{
	int		i;
	char	*ret;
	char	*tmp;
	char	*tmp2;

	if (!cmd || !cmd[0] || cmd[0][0] == '\0')
		return (NULL);
	if (!get_env_value(minishell, "PATH") || ft_strchr(cmd[0], '/'))
	{
		ret = check_absolute_path(cmd);
		return (ret);
	}
	i = 0;
	while (path && path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp2 = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		if (access(tmp2, X_OK) == 0)
			return (tmp2);
		free(tmp2);
		i++;
	}
	return (NULL);
}

void	find_path(t_minishell *minishell)
{
	t_list	*tmp;
	t_cmd	*cmd;

	tmp = minishell->cmds;
	while (tmp)
	{
		cmd = (t_cmd *)tmp->content;
		cmd->cmd_path = find_exec(minishell ,cmd->args, minishell->exec_path_tab);
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
}
