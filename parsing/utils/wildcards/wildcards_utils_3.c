/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:15:27 by zajaddad          #+#    #+#             */
/*   Updated: 2025/05/23 16:25:20 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

void	ft_swap(void **a, void **b)
{
	void	*tmp;

	if (a == NULL || b == NULL)
		return ;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	ft_case_sensitive_strcmp(char *s1, char *s2)
{
	while (ft_tolower(*s1) == ft_tolower(*s2) && ft_tolower(*s1))
	{
		s1++;
		s2++;
	}
	return (ft_tolower(*s1) - ft_tolower(*s2));
}

void	sort_matches(t_list **matches)
{
	t_list	*i;
	t_list	*j;

	if (matches == NULL || *matches == NULL)
		return ;
	i = *matches;
	while (i != NULL)
	{
		j = *matches;
		while (j->next != NULL)
		{
			if (ft_case_sensitive_strcmp(j->content, j->next->content) > 0)
			{
				ft_swap(&j->content, &j->next->content);
			}
			j = j->next;
		}
		i = i->next;
	}
}
