/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_putaddress_fd.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 23:11:46 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/21 16:07:37 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_fprintf_putaddress_fd(int fd, size_t address, int *counter)
{
	*counter += ft_fprintf_putstr_fd(fd, "0x");
	ft_fprintf_puthex_fd(fd, address, "0123456789abcdef", counter);
}
