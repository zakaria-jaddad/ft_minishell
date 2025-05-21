/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:11:10 by mouait-e          #+#    #+#             */
/*   Updated: 2025/05/18 18:22:25 by mouait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

void	ft_add_node(t_list *node_before, t_list *add)
{
	if (!node_before || !add)
		return ;
	if (node_before->next)
		add->next = node_before->next;
	add->prev = node_before;
	node_before->next = add;
}
