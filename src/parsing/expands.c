/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 09:16:51 by algasnie          #+#    #+#             */
/*   Updated: 2026/03/16 16:47:33 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*integrate_expand(char *token, char *expand_start,
							char *expand_key, char *expand_value)
{
	char	*result;
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_substr(token, 0, expand_start - token);
	tmp2 = ft_strjoin(tmp1, expand_value);
	result = ft_strjoin(tmp2, expand_start + 1 + ft_strlen(expand_key));
	free(token);
	free(tmp1);
	free(tmp2);
	return (result);
}

static char	*extract_expand(char *word)
{
	int		i;
	char	*key;

	i = 1;
	if (word[i] == '?')
		return (ft_strdup("?"));
	if (word[i] == '\'' || word[i] == '\"')
	{
		key = ft_strdup("");
		return (key);
	}
	while (word[i] && (ft_isalnum(word[i]) || word[i] == '_'))
		i++;
	if (i == 1)
		return (NULL);
	key = ft_substr(word, 1, i - 1);
	return (key);
}

char	*is_there_expands(char *word, int heredoc)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '$')
		{
			if (word[i + 1] && (ft_isalnum(word[i + 1])
					|| word[i + 1] == '_' || word[i + 1] == '?'))
			{
				if (heredoc || get_quote_state(word, i) != 1)
					return (&word[i]);
			}
			else if (word[i + 1]
				&& (word[i + 1] == '\'' || word[i + 1] == '\"'))
			{
				if (heredoc || get_quote_state(word, i) == 0)
					return (&word[i]);
			}
		}
		i++;
	}
	return (NULL);
}

char	*token_expands(t_minishell *minishell, char *token, int heredoc)
{
	char	*start;
	char	*key;
	char	*value;

	start = is_there_expands(token, heredoc);
	while (start)
	{
		key = extract_expand(start);
		if (!key)
			return (NULL);
		value = get_env_value(minishell, key);
		if (!value)
			value = ft_strdup("");
		token = integrate_expand(token, start, key, value);
		free(key);
		free(value);
		if (!token)
			return (NULL);
		start = is_there_expands(token, heredoc);
	}
	return (token);
}

int	handle_expands(t_minishell *minishell, t_list *token_list)
{
	t_token	*token;
	t_token	*token_prev;

	token_prev = NULL;
	while (token_list)
	{
		token = (t_token *)token_list->content;
		token->token = token_expands(minishell, token->token, 0);
		if (!token->token)
			return (1);
		if (token_prev && (token_prev->type >= R_INPUT
				&& token_prev->type <= R_OUTPUT_APPEND))
		{
			if (token->token[0] == '\0' || ft_strchr(token->token, ' '))
			{
				token->heredoc_fd = -1;
				ft_printf(STDERR_FILENO, "minishell: ambiguous redirect\n");
				return (1);
			}
		}
		token_prev = token;
		token_list = token_list->next;
	}
	return (0);
}
