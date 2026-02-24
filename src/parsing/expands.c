/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 09:16:51 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/24 16:01:02 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *integrate_expand(char *token, char *expand_start, char *expand_key, char *expand_value)
{
	char *result;
	char *tmp1;
	char *tmp2;
		
	tmp1 = ft_substr(token, 0, expand_start - token);
	tmp2 = ft_strjoin(tmp1, expand_value);
	result = ft_strjoin(tmp2, expand_start + 1 + ft_strlen(expand_key));
	
	free(token);
	free(tmp1);
	free(tmp2);

	return (result);
}

static char *is_there_expands(char *word)
{
	int	i;
			
	i = 0;
	while (word[i])
	{
		if (word[i] == '$')
		{
			if (get_quote_state(word, i) != 1)
				return (&word[i]);
		}
		i++;
	}
	return (NULL);
}

static char *extract_expand(char *word)
{
	int	i;
	char *key;

	i = 1;
	if (word[i] == '?')
		return (ft_strdup("?"));
	while (word[i] && (ft_isalnum(word[i]) || word[i] == '_'))
		i++;

	if (i == 1)
		return (NULL);

	key = ft_substr(word, 1, i - 1);
	return (key);
}

int	handle_expands(t_minishell *minishell, t_list *token_list)
{
	t_token	*token;
	char	*expand_start;
	char	*expand_key;
	char	*expand_value;

	while(token_list)
	{
		token = (t_token *)token_list->content;
		
		while ((expand_start = is_there_expands(token->token)) != NULL)
		{
			expand_key = extract_expand(expand_start);
			if (!expand_key)
				return (1);
			expand_value = get_env_value(minishell, expand_key);
			if (!expand_value)
				expand_value = ft_strdup("TEST_ EXPAND");
			token->token = integrate_expand(token->token, expand_start, expand_key, expand_value);
			free(expand_key);
			free(expand_value);
			if (!token->token)
				return (1);
			
		}
		token_list = token_list->next;
	}
	return (0);
}
