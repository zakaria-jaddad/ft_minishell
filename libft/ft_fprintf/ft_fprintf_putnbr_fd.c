/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_putnbr_fd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 21:50:39 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/21 16:07:45 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_fprintf_putnbr_fd(int fd, int n, int *counter)
{
	long	long_n;

	long_n = n;
	if (long_n < 0)
	{
		*counter += ft_fprintf_putchar_fd(fd, '-');
		long_n *= -1;
	}
	if (long_n >= 0 && long_n < 10)
		*counter += ft_fprintf_putchar_fd(fd, (long_n + '0'));
	else
	{
		ft_fprintf_putnbr_fd(fd, (long_n / 10), counter);
		*counter += ft_fprintf_putchar_fd(fd, ((long_n % 10) + '0'));
	}
}
