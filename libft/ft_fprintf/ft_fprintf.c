/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:36:41 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/21 16:07:30 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	print_format(int fd, char fmt, va_list ap, int *counter)
{
	if (fmt == 'c')
		*counter += ft_fprintf_putchar_fd(fd, va_arg(ap, int));
	else if (fmt == 's')
		*counter += ft_fprintf_putstr_fd(fd, va_arg(ap, char *));
	else if (fmt == 'p')
		ft_fprintf_putaddress_fd(fd, (size_t)va_arg(ap, void *), counter);
	else if (fmt == 'd' || fmt == 'i')
		ft_fprintf_putnbr_fd(fd, va_arg(ap, int), counter);
	else if (fmt == 'u')
		ft_fprintf_put_unsigned_nbr_fd(fd, va_arg(ap, unsigned int), counter);
	else if (fmt == 'x')
		ft_fprintf_puthex_fd(fd, va_arg(ap, unsigned int), "0123456789abcdef",
			counter);
	else if (fmt == 'X')
		ft_fprintf_puthex_fd(fd, va_arg(ap, unsigned int), "0123456789ABCDEF",
			counter);
	else
		*counter += ft_fprintf_putchar_fd(fd, fmt);
}

int	ft_fprintf(int fd, const char *format, ...)
{
	int		counter;
	va_list	ap;

	counter = 0;
	if (write(1, NULL, 0) == -1)
		return (-1);
	va_start(ap, format);
	while (*format)
	{
		if (*format != '%')
		{
			counter += ft_fprintf_putchar_fd(fd, *format++);
			continue ;
		}
		print_format(fd, *++format, ap, &counter);
		if (*format++ == 0)
			break ;
	}
	va_end(ap);
	return (counter);
}
