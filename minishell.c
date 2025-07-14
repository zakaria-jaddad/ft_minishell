/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:02:50 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/14 22:34:09 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static bool	is_valid_line(char *line)
{
	if (*line == 0)
		return (false);
	if (count_spaces(line) == (int)ft_strlen(line))
		return (false);
	return (true);
}

void	sig(void)
{
	if (signal(SIGINT, handle_ctr_c) == SIG_ERR)
	{
		ft_fprintf(STDERR_FILENO, "signal: error handling ctr+c!!\n");
		exit(EXIT_FAILURE);
	}
	signal(SIGQUIT, SIG_IGN);
}

void	ft_minishell(t_list *env)
{
	char			*line;
	t_cmd			*cmd;
	struct termios	tr;

	while (true)
	{
		tcgetattr(STDERR_FILENO, &tr);
		signals_handling();
		line = readline("ft_minishell -> ");
		if (line == NULL)
			(ft_lstclear(&env, free_env), _exit_(NULL));
		if (is_valid_line(line) == true)
			add_history(line);
		cmd = parse_cmd(line, env);
		if (cmd == NULL)
		{
			line = (free(line), NULL);
			continue ;
		}
		status_x(execution(cmd, &env), 1);
		clear_cmd(cmd);
		line = (free(line), NULL);
		tcsetattr(STDERR_FILENO, TCSANOW, &tr);
	}
}

int	main(int _, char **__, char **env)
{
	t_list	*env_lst;

	sig();
	if (!isatty(0) || !isatty(1) || !isatty(2))
		return (EXIT_FAILURE);
	env_lst = envs_init(env, _, __);
	if (env_lst == NULL)
		return (EXIT_FAILURE);
	ft_minishell(env_lst);
	return (EXIT_SUCCESS);
}
