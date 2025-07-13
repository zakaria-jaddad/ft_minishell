/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 07:46:53 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/13 00:26:57 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../../libft/libft.h"
# include <stdbool.h>

typedef struct s_env
{
	char	*key;
	char	*value;
}			t_env;

t_list		*envs_init(char **env, ...);
t_list		*append_env(t_list **env_lst, char *key, char *value);
t_env		*get_env(t_list *env_lst, char *key);
t_env		*edit_env(t_env *env, char *new_value);
void		free_env(void *env);

#endif // !ENV_H
