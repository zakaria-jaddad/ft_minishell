/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:01:43 by mouait-e          #+#    #+#             */
/*   Updated: 2025/05/13 16:38:43 by mouait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include <sys/wait.h> // wait()
# include <unistd.h>

int		_echo_(char **args, int fd);
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

#endif
