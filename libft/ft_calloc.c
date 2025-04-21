/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 22:15:13 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/21 16:03:57 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t		len;
	void		*ptr;

	len = count * size;
	ptr = malloc(len);
	if (ptr == NULL)
		return (NULL);
	ft_memset(ptr, 0, len);
	return (ptr);
}
