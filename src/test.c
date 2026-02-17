/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:23:10 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/17 16:51:20 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// print de l'init de la liste chainee
void test_print_env(t_list *env)
{
	t_env	*current;
	
	while (1)
	{
		current = (t_env *)env->content;
		printf("KEY == %s\nVALUE == %s \n\n", current->key, current->value);

		if (!env->next)
			break ;
		env = env->next;
	}
}


/// test de la recherche de la VALUE dans l'env
void test_print_env_value(t_list *env, char *key)
{
	char *value;

	value = get_env_value(env, key);
	printf("Key: %s Value: %s\n", key, value);
}

/// test du tableau des paths des exec
void	test_print_exec_path_tab(char **exec_path_tab)
{
	int	i;

	i = 0;
	while (exec_path_tab[i])
	{
		printf("%s\n", exec_path_tab[i]);
		i++;
	}
}


// /// print de la liste chainee de token
void	test_print_list_token(t_list *token_list)
{
	t_token	*token;

	while (1)
	{
		token = (t_token *)token_list->content;
		printf("%s\n", token->token);
		if (token->type == 0)
			printf("WORD\n");
		if (token->type == 1)
			printf("PIPE\n");
		if (token->type == 2)
			printf("R_INPUT\n");
		if (token->type == 3)
			printf("R_OUTPUT\n");
		if (token->type == 4)
			printf("R_OUTPUT_APPEND\n");
		if (token->type == 5)
			printf("HEREDOC\n");
		if (!token_list->next)
			break ;
		printf("\n");
		token_list = token_list->next;
	}
}

void test_print_minish_cmds(t_minishell *minishell)
{
	t_cmd	*cmd;
	t_minishell	*tmp;
	int		i;
	int		y;
	

	tmp = minishell;
	y = 0;
	while (tmp->cmds)
	{
		i = 0;
		cmd = (t_cmd *)tmp->cmds->content;
		printf("minish_cmds %i: ", y);
		while (cmd->args[i])
		{
			printf("cmd: %s", cmd->args[i]);
			i++;
		}
		printf("\n");
		printf("path: %s\n\n", cmd->cmd_path);
		if (!tmp->cmds->next)
			break ;
		
		tmp->cmds = tmp->cmds->next;
		y++;
	}
	
}