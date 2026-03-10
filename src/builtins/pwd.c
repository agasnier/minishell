/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:49:04 by masenche          #+#    #+#             */
/*   Updated: 2026/03/10 16:01:45 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_minishell *minishell, t_cmd *cmd)
{
	char	*pwd;
	char	cwd[1024];

	(void)cmd;
	pwd = get_env_value(minishell, "PWD");
	if (pwd)
	{
		printf("%s\n", pwd);
		free(pwd);
		return (0);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		return (0);
	}
	else
	{
		perror("minishell: pwd");
		return (1);
	}
}
