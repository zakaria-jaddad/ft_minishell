/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:01:43 by mouait-e          #+#    #+#             */
/*   Updated: 2025/06/29 21:34:52 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "./parsing/parsing.h"
# include <errno.h>
# include <fcntl.h> // open
# include <signal.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h> // wait()
# include <termios.h>
# include <unistd.h>

int		_echo_(char **args);
int		_cd_(t_list *list, char **args);
int		_pwd_(char *pwd);
int		_export_(t_list *list, char **args);
int		_env_(t_list *list);
void	_exit_(char **args);
void	print_error(char *err, char *value, char *message);
t_list	*find_node(t_list *envs, char *key);
char	**list_to_double_pointer(t_list *env_list);
int		count_envs(t_list *envs);
void	free_double_pointer(void **p);
void	_unset_(t_list *envs, char **args);
t_list	*sort_envs(t_list *list);
char	**envs_list_to_double_pointer(t_list *env_list);
char	*manage_pwd(char *value);
int		execution(t_cmd *tree, t_list *env_list);
char	*list_to_string(t_list *list);
char	*run_heredoc(char *dilimiter, int expand, t_list *env_list);
int		run_redir(t_cmd *t, t_list *envs);
int		run_in_pipe(t_cmd *t, t_list *envs);

// helpers
int		count_args(t_list *tokens);
char	**arr_add_front(char **to_add, char **arr);
void	setup_pwd(t_env *pwd);

// file handling
int		open_file(char *file, int flags);
int		open_file(char *file, int flags);
int		found_file(t_cmd *t, t_node_type flag, t_list *envs);

// signals
void	handle_ctrC_fork(int sig);

#endif
