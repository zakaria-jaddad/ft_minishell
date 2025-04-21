/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:26:55 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/21 16:06:16 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*needle == 0)
		return ((char *) haystack);
	if (len == 0)
		return (NULL);
	while (*haystack)
	{
		j = 0;
		while (needle[j] && needle[j] == haystack[j] && j + i < len)
			j++;
		if (needle[j] == 0)
			return ((char *) haystack);
		haystack++;
		i++;
	}
	return (NULL);
}
