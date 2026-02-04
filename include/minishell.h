/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:05:58 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/04 18:32:47 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_path
{
	char			*path;
	struct s_env	*next;
}	t_path;

typedef struct	s_minishell
{
	t_list	*env;
	struct s_path	*path;
	
}	t_minishell;


//main.c
int	main(int argc, char *argv[], char **envp);

//test.c
void test_print_env(t_list *env);
void test_print_env_value(t_env *env, char *key);


//env_init.c
void	env_add_back(t_env **lst, t_env *new);
void	free_env_list(t_env **env_list);
t_list	*init_env(char **envp);

//env_utils.c
char *get_env_value(t_env *env, char *key);

//env_path.c
t_path	*get_exec_path(t_minishell *minishell);
