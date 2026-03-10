/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 16:25:35 by algasnie          #+#    #+#             */
/*   Updated: 2026/03/10 14:47:27 by masenche         ###   ########.fr       */
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

static char	*check_path(t_minishell *minishell, char **cmd)
{
	char	*path_env;
	char	*ret;

	path_env = get_env_value(minishell, "PATH");
	if (!path_env || ft_strchr(cmd[0], '/'))
	{
		ret = check_absolute_path(cmd);
		free (path_env);
		return (ret);
	}
	free (path_env);
	return (NULL);
}

static int	is_directory(char *path)
{
	struct stat	statbuf;
	int			ret;

	if (stat(path, &statbuf) != 0)
		return (0);
	ret = S_ISDIR(statbuf.st_mode);
	return (ret);
}

static char	*find_exec(t_minishell *minishell, char **cmd, char **path)
{
	int		i;
	char	*full_path;
	char	*tmp;

	if (!cmd || !cmd[0] || cmd[0][0] == '\0')
		return (NULL);
	full_path = check_path(minishell, cmd);
	if (full_path)
		return (full_path);
	i = 0;
	while (path && path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		full_path = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		if (access(full_path, X_OK) == 0 && !is_directory(full_path))
			return (full_path);
		free(full_path);
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
		cmd->cmd_path = find_exec(minishell, cmd->args,
				minishell->exec_path_tab);
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
}
