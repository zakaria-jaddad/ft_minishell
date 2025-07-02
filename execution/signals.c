/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:06:15 by mouait-e          #+#    #+#             */
/*   Updated: 2025/07/01 16:06:15 by mouait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_ctr_c_fork(int sig)
{
	(void)sig;
	exit(1);
}

void	handle_ctr_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	status_x(1, 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
