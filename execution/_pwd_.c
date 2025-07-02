/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _pwd_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:23:14 by mouait-e          #+#    #+#             */
/*   Updated: 2025/05/19 22:51:15 by mouait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

int	status_x(int value, int modify)
{
	static int	s;

	if (modify)
		s = value;
	return (s);
}

int	_pwd_(char *pwd)
{
	if (!pwd)
		pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	printf("%s\n", pwd);
	return (0);
}
