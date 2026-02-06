/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 10:14:05 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/06 11:15:16 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_exec(char *cmd, char **path)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	if (!cmd)
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (strdup(cmd));
	i = 0;
	while (path && path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp2 = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(tmp2, X_OK) == 0)
			return (tmp2);
		free(tmp2);
		i++;
	}
	return (NULL);
}

void	find_path()
{
	int	arg;
	int	cmds;

	arg = 2;
	cmds = 0;
	while (arg < pipex_data->argc - 1)
	{
		pipex_data->cmds[cmds].path = find_exec(pipex_data->cmds[cmds].cmd[0],
				pipex_data->path);
		cmds++;
		arg++;
	}
}