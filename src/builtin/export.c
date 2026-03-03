/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:49:13 by masenche          #+#    #+#             */
/*   Updated: 2026/03/03 16:33:00 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	search_export(t_list *env_list, t_env *export)
{
	t_list	*tmp;
	t_env	*env_node;

	tmp = env_list;
	while (tmp)
	{
		env_node = (t_env *)tmp->content;
		if (ft_strcmp(env_node->key, export->key) == 0)
		{
			if (export->value)
			{
				free(env_node->value);
				env_node->value = export->value;
			}
			free(export->key);
			free(export);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

static int	fill_env_data(t_env *new_node, char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	new_node->key = ft_substr(str, 0, i);
	new_node->exported = 1;
	if (!new_node->key)
		return (0);
	if (str[i])
	{
		new_node->value = ft_strdup(str + i + 1);
		if (!new_node->value)
		{
			free(new_node->key);
			return (0);
		}
	}
	else
		new_node->value = NULL;
	return (1);
}

static int	verify_export_syntax(char *str)
{
	int	i;

	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (1);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

static int	builtin_export_helper(t_cmd *cmd, t_minishell *minishell, int i)
{
	t_env	*export;
	t_list	*new_node;

	export = malloc(sizeof(t_env));
	if (!export)
		return (1);
	if (fill_env_data(export, cmd->args[i]) == 0)
	{
		free(export);
		return (1);
	}
	if (search_export(minishell->env, export) == 0)
	{
		new_node = ft_lstnew(export);
		if (!export || !new_node)
		{
			free_env(export);
			return (1);
		}
		ft_lstadd_back(&minishell->env, new_node);
	}
	return (0);
}

int	builtin_export(t_cmd *cmd, t_minishell *minishell)
{
	int		i;

	if (!cmd->args[1])
	{
		export_print_env(minishell);
		return (0);
	}
	i = 1;
	while (cmd->args[i])
	{
		if (verify_export_syntax(cmd->args[i]))
			printf("minishell: export: `%s': not a valid identifier",
				cmd->args[i]);
		else
		{
			if (builtin_export_helper(cmd, minishell, i))
				return (1);
		}
		i++;
	}
	return (0);
}
