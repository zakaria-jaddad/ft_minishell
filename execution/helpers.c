/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:36:41 by mouait-e          #+#    #+#             */
/*   Updated: 2025/07/01 10:36:41 by mouait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

int	count_args(t_list *tokens)
{
	int		i;
	t_token	*token;

	if (!tokens || !tokens->content)
		i = 0;
	else
		i = 1;
	while (tokens)
	{
		token = tokens->content;
		if (token->type == TOKEN_WHITE_SPACE)
			i++;
		tokens = tokens->next;
	}
	return (i);
}

int	count_arr(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

char	**arr_add_front(char **to_add, char **arr)
{
	char	**rv;
	int		i;
	int		j;

	if (!to_add)
		return (arr);
	if (!arr)
		return (to_add);
	i = count_arr(arr) + count_arr(to_add);
	rv = malloc(sizeof(char *) * (i + 1));
	if (!rv)
		return (NULL);
	i = -1;
	while (to_add[++i])
		rv[i] = ft_strdup(to_add[i]);
	j = -1;
	while (arr[++j])
		rv[i++] = ft_strdup(arr[j]);
	rv[i] = NULL;
	free_double_pointer((void **)arr);
	free_double_pointer((void **)to_add);
	return (rv);
}

void	setup_pwd(t_env *pwd)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
		manage_pwd(cwd);
	else if (pwd)
		manage_pwd(pwd->value);
}
