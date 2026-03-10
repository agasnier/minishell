/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:48:54 by masenche          #+#    #+#             */
/*   Updated: 2026/03/10 16:51:23 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_target_dir(t_cmd *cmd, t_minishell *minish, char **target,
				int *prt)
{
	*prt = 0;
	if (cmd->args[1] == NULL)
	{
		*target = get_env_value(minish, "HOME");
		if (!*target)
			return (ft_printf(2, "minishell: cd: HOME not set\n"), 1);
		if ((*target)[0] == '\0')
			return (2);
	}
	else if (ft_strncmp(cmd->args[1], "-", 2) == 0)
	{
		*target = get_env_value(minish, "OLDPWD");
		if (!*target)
			return (ft_printf(2, "minishell: cd: OLDPWD not set\n"), 1);
		*prt = 1;
	}
	else
		*target = ft_strdup(cmd->args[1]);
	return (0);
}

static int	init_cd(t_cmd *cmd, t_minishell *minish, char **target, int *prt)
{
	int	status;

	if (cmd->args[1] && cmd->args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	status = get_target_dir(cmd, minish, target, prt);
	if (status == 1)
		return (1);
	if (status == 2)
	{
		free(*target);
		return (2);
	}
	return (0);
}

static void	update_env_vars(char *old_pwd,
	t_minishell *minishell, char *target_dir)
{
	char	cwd[4096];
	char	*tmp;
	char	*new_pwd;

	if (old_pwd)
		update_env_value(minishell, "OLDPWD", old_pwd);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		update_env_value(minishell, "PWD", cwd);
	else
	{
		ft_printf(2, "cd: error retrieving current directory: \
getcwd: cannot access parent directories: %s\n", strerror(errno));
		if (old_pwd && target_dir && target_dir[0] == '/')
			update_env_value(minishell, "PWD", target_dir);
		else if (old_pwd && target_dir)
		{
			tmp = ft_strjoin(old_pwd, "/");
			new_pwd = ft_strjoin(tmp, target_dir);
			update_env_value(minishell, "PWD", new_pwd);
			free(tmp);
			free(new_pwd);
		}
	}
}

static int	target_is_valid(char *target_dir)
{
	if (chdir(target_dir) == -1)
	{
		ft_printf(2, "minishell: cd: %s: %s\n", target_dir, strerror(errno));
		return (1);
	}
	return (0);
}

int	builtin_cd(t_cmd *cmd, t_minishell *minishell)
{
	char	*target_dir;
	char	*old_pwd;
	char	actual_old_pwd[4096];
	int		print_path;
	int		status;

	status = init_cd(cmd, minishell, &target_dir, &print_path);
	if (status != 0)
		return (status == 1);
	if (getcwd(actual_old_pwd, sizeof(actual_old_pwd)) != NULL)
		old_pwd = ft_strdup(actual_old_pwd);
	else
		old_pwd = get_env_value(minishell, "PWD");
	if (target_is_valid(target_dir) != 0)
	{
		free(old_pwd);
		free(target_dir);
		return (1);
	}
	if (print_path)
		ft_printf(1, "%s\n", target_dir);
	update_env_vars(old_pwd, minishell, target_dir);
	free(old_pwd);
	free(target_dir);
	return (0);
}
