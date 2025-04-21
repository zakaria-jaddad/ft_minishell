/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_put_unsigned_nbr_fd.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 22:18:15 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/21 16:07:34 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_fprintf_put_unsigned_nbr_fd(int fd, unsigned int n, int *counter)
{
	if (n < 10)
		*counter += ft_fprintf_putchar_fd(fd, (n + '0'));
	else
	{
		ft_fprintf_putnbr_fd(fd, (n / 10), counter);
		*counter += ft_fprintf_putchar_fd(fd, ((n % 10) + '0'));
	}
}
