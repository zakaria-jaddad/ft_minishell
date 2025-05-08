/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:01:43 by mouait-e          #+#    #+#             */
/*   Updated: 2025/05/08 02:19:17 by mouait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include <unistd.h>

int		_echo_(char **args, int fd);
int		_cd_(t_list *list, char **args);
int		_pwd_(t_list *env);
int		_export_(t_list *list, char **args);
int		_env_(t_list *list);
void	_exit_(char **args);
void	print_error(char *err, char *value, char *message);
t_list	*find_node(t_list *envs, char *key);
char	**list_to_double_pointer(t_list *env_list);
int		count_envs(t_list *envs);
void	free_double_pointer(void **p);
void	ft_lst_rm_one(t_list *nodeToDel, void clear_content(t_env *content));
void	_unset_(t_list *envs, char **args);

#endif
