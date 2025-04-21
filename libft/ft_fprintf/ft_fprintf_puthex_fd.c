/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_puthex_fd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 22:37:46 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/21 16:07:42 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_fprintf_puthex_fd(int fd, size_t n, const char *base, int *counter)
{
	size_t	base_len;

	base_len = ft_fprintf_strlen(base);
	if (n >= base_len)
		ft_fprintf_puthex_fd(fd, (n / base_len), base, counter);
	*counter += ft_fprintf_putchar_fd(fd, base[n % base_len]);
}
