/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:19:53 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/25 09:19:37 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	syntax_token_list(t_token *token, t_token *next)
{
	if (token->type == PIPE && (!next || next->type == PIPE))
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	if (token->type >= R_INPUT && token->type <= HEREDOC)
	{
		if (!next)
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return (1);
		}
		if (next->type != WORD)
		{
			printf("minishell: syntax error near unexpected token `%s'\n", next->token);
			return (1);
		}
	}
	return (0);
}

static int	verify_token_list(t_list *token_list)
{
	t_token	*token;
	t_token	*next_token;
	
	if (((t_token *)token_list->content)->type == PIPE)
	{
		printf("syntax error near unexpected token `|'\n");
		return (1);
	}

	while (token_list)
	{
		token = (t_token *)token_list->content;
		next_token = NULL;
		if (token_list->next)
			next_token = (t_token *)token_list->next->content;
		if (syntax_token_list(token, next_token))
			return (1);
		token_list = token_list->next; 
		
	}
	return (0);
}

static t_cmd *init_cmd_struct(void)
{	
	t_cmd *cmd;
	
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->cmd_path = NULL;
	cmd->fd_in = -1;
	cmd->fd_out = -1;
	return (cmd);
}

static int	count_args(t_list *token_list)
{
	t_token	*token;
	int		args_count;

	args_count = 0;

	while (token_list)
	{
		token = (t_token *)token_list->content;
		if (token->type == PIPE)
			break ;
		else if (token->type >= R_INPUT && token->type <= HEREDOC)
		{
			if (token_list->next)
				token_list = token_list->next;
		}
		else if (token->type == WORD)
			args_count++;

		token_list = token_list->next;
	}
	return (args_count);
}

static int	format_cmds(t_minishell *minishell, t_list *token_list)
{
	t_cmd	*cmd;
	t_token	*token;
	int		args_count;
	t_list	*new_node;
	int		i;
	
	

	minishell->cmds = NULL;

	while (token_list)
	{
		cmd = init_cmd_struct();
		if (!cmd)
			return (1);

		args_count = count_args(token_list);
		cmd->args = malloc(sizeof(char *) * (args_count + 1));
		if (!cmd->args)
		{
			free(cmd);
			return (1);
		}
		
		i = 0;
		while (token_list)
		{
			token = (t_token *)token_list->content;
			if (token->type == PIPE)
			{
				token_list = token_list->next;
				break ;
			}
			else if (token->type >= R_INPUT && token->type <= HEREDOC)
			{
				if (token_list->next)
					token_list = token_list->next;
			}
			else if (token->type == WORD)
			{
				cmd->args[i] = token->token;
				i++;
			}
			token_list = token_list->next;
		}
		cmd->args[i] = NULL;
		new_node = ft_lstnew(cmd);
		if (!new_node)
		{
			free(cmd->args);
			free(cmd);
			return (1);
		}
		ft_lstadd_back(&minishell->cmds, new_node);
		
	}
	return (0);
		
}

static void remake_token_list(t_list **token_list)
{
	t_token	*token;
	t_list	*current;
	t_list	*prev;
	t_list	*tmp;
	char	**tokens;
	int		i;
	t_list	*sub_current;
	t_token	*sub_token;
	
	current = *token_list;
	prev = NULL;
	tmp = NULL;

	sub_token = NULL;

	
	while (current)
	{
		token = (t_token *)current->content;
		if (!token->token || token->token[0] == '\0')
		{
			if (prev)
				prev->next = current->next;
			else
				*token_list = current->next;
			tmp = current;
			current = current->next;
			free_token(tmp->content);
			free(tmp);
			continue ;
		}
		if (ft_strchr(token->token, ' '))
		{
			tokens = ft_split_unquoted(token->token, ' ');

			if (tokens && tokens[0])
			{
				free(token->token);
				token->token = ft_strdup(tokens[0]);
				if (!token->token)
					return ;
			}
			
			i = 1;
			while (tokens[i])
			{
				sub_token = malloc(sizeof(t_token));
				if (!sub_token)
					return ; //////////////////////////////////////////////
				sub_token->token = ft_strdup(tokens[i]);
				if (!sub_token->token)
					break ; ///////////////////////
				sub_token->type = WORD;
				sub_current = ft_lstnew(sub_token);
				if (!sub_current)
					return ;/////////////////////////////////////////

				sub_current->next = current->next;
				current->next = sub_current;

				prev = current;
				current = sub_current;
				
				i++;
			}
			free_tab(tokens);
		}
		prev = current;
		current = current->next;
	}
}

void	parsing_prompt(t_minishell *minishell, char *prompt)
{
	t_list	*token_list;
	
	if (verify_unclosed_quotes(prompt))
		return ;
	
	token_list = list_token(prompt);

	if (!token_list)
		return ;
		
	if (verify_token_list(token_list))
	{
		minishell->exit_status = 2;
		ft_lstclear(&token_list, free_token);
		return ;
	}




	//gerer les expands ici
	if (handle_expands(minishell, token_list))
		return ;
	
	remake_token_list(&token_list);

	//remove des quotes ici

	if (format_cmds(minishell, token_list))
	{
		ft_lstclear(&token_list, free_token);
		printf("minishell: memory allocation fail\n");
		return ;
	}

	find_path(minishell);






	
	//trouver le path de chaque commande
	//verifier infile && outfile
	//execution


	////test//////////////
	test_print_list_token(token_list);
	//test_print_minish_cmds(minishell);
	/////////////////////////


	
}