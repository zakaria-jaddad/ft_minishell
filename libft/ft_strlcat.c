/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:53:31 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/21 16:05:56 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t	len;

	len = 0;
	while (len < maxlen)
	{
		if (!*s++)
			break ;
		len++;
	}
	return (len);
}

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dest_len;
	size_t	src_len;

	i = 0;
	j = 0;
	src_len = ft_strlen(src);
	dest_len = ft_strnlen(dest, dstsize);
	if (dstsize == 0)
		return (src_len);
	else if (dstsize == dest_len)
		return (src_len + dstsize);
	while (dest[i])
		i++;
	while (src[j] && i < dstsize - 1)
		dest[i++] = src[j++];
	dest[i] = 0;
	return (dest_len + src_len);
}
