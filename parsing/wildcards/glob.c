/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:56:07 by zajaddad          #+#    #+#             */
/*   Updated: 2025/05/23 15:56:57 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/parsing.h"

bool	glob(const char *pattern, const char *text)
{
	while (*pattern != 0 && *text != 0)
	{
		if (*pattern == '*')
		{
			if (glob(pattern + 1, text) == true)
				return (true);
			text += 1;
		}
		else if (*pattern == *text)
			(void)(pattern++, text++);
		else
			return (false);
	}
	if (*text == 0)
	{
		while (*pattern == '*')
			pattern += 1;
		return (*pattern == 0);
	}
	return (false);
}

void	check_glob(const char *pattern, const char *text)
{
	bool	result;

	result = glob(pattern, text);
	if (result == true)
	{
		printf("%s <=> %s => true\n", pattern, text);
	}
	else
	{
		printf("%s <=> %s => false\n", pattern, text);
	}
}
