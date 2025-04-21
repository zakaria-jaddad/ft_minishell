/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 01:53:47 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/21 16:06:23 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	start_pos;
	int	end_pos;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start_pos = 0;
	end_pos = ft_strlen(s1);
	if (*s1 == 0)
		return (ft_strdup(""));
	while (ft_strchr(set, s1[start_pos]))
		start_pos++;
	while (ft_strchr(set, s1[end_pos]))
		end_pos--;
	end_pos++;
	return (ft_substr(s1, start_pos, (end_pos - start_pos)));
}
