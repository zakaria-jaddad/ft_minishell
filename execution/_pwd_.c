/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _pwd_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:23:14 by mouait-e          #+#    #+#             */
/*   Updated: 2025/05/04 12:23:38 by mouait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

int	_pwd_(t_list *list)
{
	t_env	*pwd;

	if (!list)
		return (-1);
	pwd = find_var(list, "PWD");
	if (!pwd)
		return (-1);
	printf("%s\n", pwd->value);
	return (0);
}
