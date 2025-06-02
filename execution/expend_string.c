/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:16:37 by mouait-e          #+#    #+#             */
/*   Updated: 2025/05/23 12:37:20 by mouait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

int	status_x(int value, int modify)
{
	static int	s;

	if (modify)
		s = value;
	return (s);
}

t_list	*expand(char **args, t_list *envs)
{
	char	**x;
	t_list	*lst;
	int		i;
	int		j;

	if (!args || !*args || !envs)
		return (NULL);
	lst = NULL;
	j = -1;
	while (args[++j])
	{
		i = 0;
		x = ft_split(args[j], '$');
		if (!x[i + 1] && args[j][0] != '$')
		{
			ft_lstadd_back(&lst, ft_lstnew(x[i]));
			free(x);
			continue ;
		}
		if (args[j][i--] != '$')
			ft_lstadd_back(&lst, ft_lstnew(x[++i]));
		while (x[++i])
			if (get_env(envs, x[i]) && get_env(envs, x[i])->value)
				ft_lstadd_back(&lst, ft_lstnew(get_env(envs, x[i])->value));
			else if (x[i][0] == '?')
				ft_lstadd_back(&lst, ft_lstnew(ft_strjoin(ft_itoa(status_x(0,
									0)), x[i] + 1)));
		if (args[j + 1])
			ft_lstadd_back(&lst, ft_lstnew(" "));
		free_double_pointer((void **)x);
	}
	return (lst);
}
