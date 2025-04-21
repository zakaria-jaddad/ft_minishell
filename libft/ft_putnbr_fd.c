/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:05:27 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/21 16:02:17 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	long_n;

	long_n = n;
	if (long_n < 0)
	{
		write(fd, "-", 1);
		long_n *= -1;
	}
	if (long_n >= 0 && long_n < 10)
		ft_putchar_fd((long_n + '0'), fd);
	else
	{
		ft_putnbr_fd(((long_n / 10)), fd);
		ft_putchar_fd(((long_n % 10) + '0'), fd);
	}
}
