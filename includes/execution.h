/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:01:43 by mouait-e          #+#    #+#             */
/*   Updated: 2025/05/03 16:55:20 by mouait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include <unistd.h>

int		_echo_(char **args, int fd);
int		_cd_(t_list *list);
int		_pwd_(t_list *env);
int		_export_(t_list *list, char **args);
int		_unset_(void);
int		_env_(t_list *list, char **args);
void	_exit_(char **args);
void	print_error(char *err, char *value, char *message);

#endif
