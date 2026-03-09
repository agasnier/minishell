/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 09:35:13 by algasnie          #+#    #+#             */
/*   Updated: 2026/03/09 15:10:49 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "ft_printf.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include <string.h>

typedef struct s_env
{
	char	*key;
	char	*value;
	int		exported;		
}	t_env;

typedef struct s_cmd
{
	char	**args;
	char	*cmd_path;
	int		fd_in;
	int		fd_out;
	int		delim_quoted;
}	t_cmd;

typedef struct s_minishell
{
	t_list	*env;
	char	**exec_path_tab;
	t_list	*cmds;
	int		exit_status;
}	t_minishell;

typedef enum e_type
{
	WORD,
	PIPE,
	R_INPUT,
	R_OUTPUT,
	R_OUTPUT_APPEND,
	HEREDOC,
}	t_type;

typedef struct s_token
{
	char	*token;
	t_type	type;
	int		quoted;
}	t_token;

typedef struct s_pipeline
{
	int		prev_read_fd;
	char	**env_tab;
	int		pipe_fds[2];
}	t_pipeline;

extern volatile sig_atomic_t	g_receive_message;

//builtins
// cd.c
int		builtin_cd(t_cmd *cmd, t_minishell *minishell);
// echo.c
int		builtin_echo(t_cmd *cmd);
// env.c
int		builtin_env(t_minishell *minishell);
// exit.c
int		builtin_exit(t_minishell *minishell, t_cmd *cmd);
// export.c
int		builtin_export(t_cmd *cmd, t_minishell *minishell);
// print_export. c
int		export_print_env(t_minishell *minishell);
// pwd.c
int		builtin_pwd(t_cmd *cmd);
// unset.c
int		builtin_unset(t_cmd *cmd, t_minishell *minishell);

//env
//env_init.c
t_list	*init_env(char **envp);
//env_path.c
char	**get_exec_path(t_minishell *minishell);
void	update_env_value(t_minishell *minishell, char *key, char *new_value);
//env_utils.c
char	*get_env_value(t_minishell *minishell, char *key);

//exec
//builtins.c
int		is_builtin(char *cmd);
int		execute_builtin(t_cmd *cmd, t_minishell *minishell);
void	builtin_status_exit(t_cmd *cmd, t_minishell *minishell);
//conv.c
char	**convert_env_to_tab(t_list *env_list);
//exec_main.c
void	exe_child(t_cmd *cmd, t_minishell *minishell, char **env_tab);
void	exec_fork(t_cmd *cmd, char **env_tab, t_minishell *minishell);
void	wait_all_children(pid_t last_pid, t_minishell *minishell);
pid_t	ft_fork(t_pipeline pipeline, t_cmd *cmd,
			t_minishell *minishell, t_list *curr);
void	execute_pipeline(t_minishell *minishell, t_cmd *cmd);
void	exec_command(t_minishell *minishell);
//exec_path.c
void	find_path(t_minishell *minishell);

//parsing
//cmds_builder.c
int		format_cmds(t_minishell *minishell, t_list *token_list);
//expands.c
char	*is_there_expands(char *word, int heredoc);
char	*token_expands(t_minishell *minishell, char *token, int heredoc);
int		handle_expands(t_minishell *minishell, t_list *token_list);
//lexer.c
t_list	*list_token(char *prompt);
//parser.c
void	parsing_prompt(t_minishell *minishell, char *prompt);
//post_expands_helper.c
int		word_split(t_list **current);
//post_expands
int	remake_token_list(t_list **token_list);
//quotes.c
int		get_len_unquoted(char *str);
char	*remove_token_quotes(char *str);
void	update_quote_state(char c, int *state);
int		get_quote_state(char *str, int index);
int		verify_unclosed_quotes(char *prompt);
//syntax.c
int		verify_token_list(t_list *token_list);
//token_type.c
int		handle_token_type(t_minishell *minishell, t_cmd *cmd,
			t_list **token_list);

//signal
//signal.c
void	handle_signal(int sig);

//utils
//close_fd.c
void	close_fd(int prev_read_fd, t_list *curr, int *pipe_fds);
int		close_read_fd(int *pipe_fds);
void	exe_fd(t_cmd *cmd);
//free.c
void	free_token(void *content);
void	free_cmds(void *content);
void	free_env(void *content);
void	free_tab(char **tab);
void	free_all(t_minishell *minishell);
//ft_split_unquoted.c
char	**ft_split_unquoted(char const *s, char c);
//utils.c
int		count_args_list(t_list *token_list);

//main.c
int		main(int argc, char *argv[], char **envp);

//test.c
void	test_print_env(t_list *env);
void	test_print_exec_path_tab(char **exec_path_tab);
void	test_print_list_token(t_list *token_list);
void	test_print_minish_cmds(t_minishell *minishell);

#endif
