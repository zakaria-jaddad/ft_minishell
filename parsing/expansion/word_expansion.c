/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:04:48 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/09 15:05:45 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing/expansion.h"
#include <stdio.h>

static char	*get_key(char *str, char *special)
{
	int	special_pos;

	special_pos = 0;
	while (str[special_pos] != 0 && &str[special_pos] != special)
		special_pos++;
	return (ft_substr(str, 0, special_pos));
}

static void	special_word_expansion(char **str, char *special, t_list *env)
{
	char	*key;
	char	*tmp;
	t_env	*var;
	char *foo;

	if (str == NULL || *str == NULL || env == NULL || special == NULL)
		return ;
	key = get_key(*str, special);
	if (key == NULL)
		return ;
	var = get_env(env, key);
	tmp = *str;
	if (var == NULL)
		foo = ft_strjoin("", special);
	else
		foo  = ft_strjoin(var->value, special);
	if (foo == NULL)
		return;
	*str = foo;
	free(tmp);
	free(key);
	return ;
}

static void	simple_word_expansion(char **str, t_list *env)
{
	char	*tmp;
	t_env	*var;
	char *foo;

	if (str == NULL || *str == NULL || env == NULL)
		return ;
	tmp = *str;
	if (ft_strcmp(*str, "?") == 0)
	{
		foo = ft_itoa(status_x(0, false));
		if (foo == NULL)
			return ;
		*str = foo;
		free(tmp);
		return ;
	}
	var = get_env(env, *str);
	if (var == NULL || var->value == NULL)
		foo = NULL; // might segfault
	else
		foo  = ft_strdup(var->value);
	*str = foo;
	free(tmp);
}

void	word_expansion(char **str, t_list *env)
{
	char	*special;

	if (str == NULL || *str == NULL)
		return ;
	special = ft_strpbrk(*str, SPECIAL_EXPANSION);
	if (special != NULL)
		return (special_word_expansion(str, special, env));
	simple_word_expansion(str, env);
}

void	digit_expansion(char **str)
{
	char	*new_value;
	char	*tmp;

	if (str == NULL || *str == NULL)
		return ;
	new_value = ft_strdup(*str + 1);
	if (new_value == NULL)
		return ;
	tmp = *str;
	*str = new_value;
	free(tmp);
	return ;
}
