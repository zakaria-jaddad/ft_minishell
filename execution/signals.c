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
#include <sys/wait.h>
#include <unistd.h>

void	handle_ctr_c_fork(int sig)
{
	(void)sig;
	exit(1);
}

void	handle_ctr_c(int sig)
{
	(void)sig;
	if (!waitpid(-1, &sig, WNOHANG))
		return ;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
	rl_redisplay();
	status_x(1, 1);
}

void	signals_handling(void)
{
	struct termios	termios;

	tcgetattr(0, &termios);
	termios.c_lflag &= ~ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW, &termios);
}
