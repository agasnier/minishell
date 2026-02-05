/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:05:58 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/05 13:31:03 by algasnie         ###   ########.fr       */
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
}	t_env;

typedef struct	s_minishell
{
	t_list	*env;
	char	**exec_path_tab;
	
}	t_minishell;


//main.c
int	main(int argc, char *argv[], char **envp);

//test.c
void test_print_env(t_list *env);
void test_print_env_value(t_list *env, char *key);
void	test_print_exec_path_tab(char **exec_path_tab);


// env/
//env_init.c
t_list	*init_env(char **envp);

//env_utils.c
char *get_env_value(t_list *env, char *key);

//env_path.c
char	**get_exec_path(t_minishell *minishell);


// utils/
//free.c
void	free_env(void *content);
void	free_tab(char **tab);
void	free_all(t_minishell *minishell);
