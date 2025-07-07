/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 03:07:49 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/07 03:28:27 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/syntax_check.h"

static bool	is_empty_subshell(t_list *tokens)
{
	t_token	*tok;

	if (tokens == NULL)
		return (true);
	while (tokens)
	{
		tok = tokens->content;
		if (tok->type != TOKEN_WHITE_SPACE)
			return (false);
		tokens = tokens->next;
	}
	return (true);
}

static bool	check_after_par(t_list **tokens, t_list **subshell)
{
	if (tokens == NULL || subshell == NULL)
		return (false);
	if (*tokens == NULL)
		return (ft_fprintf(STDERR_FILENO, OPEN_PER_SE), ft_lstclear(subshell,
				free_token), false);
	if (is_empty_subshell(*subshell) == true)
		return (ft_fprintf(STDERR_FILENO, CLOSE_PER_SE), ft_lstclear(subshell,
				free_token), false);
	if (peak_next(*tokens) == TOKEN_PAR_OPEN)
		return (ft_fprintf(STDERR_FILENO, OPEN_PER_SE), ft_lstclear(subshell,
				free_token), false);
	if (is_type_word(peak_next(*tokens)) == true)
	{
		return (ft_fprintf(STDERR_FILENO, SE), ft_lstclear(subshell,
				free_token), false);
	}
	*tokens = (*tokens)->next;
	return (true);
}

static void	check_par_depth(t_token_type type, int *depth)
{
	if (type == TOKEN_PAR_OPEN)
		(*depth)++;
	else if (type == TOKEN_PAR_CLOSE)
		(*depth)--;
}

t_list	*get_subshell(t_list **t)
{
	t_list	*s_sh;
	t_list	*token_node;
	t_token	*tok;
	int		depth;

	(void)!(depth = 1, s_sh = NULL);
	if (is_type_word(peak_prev(*t)) == true)
		return (ft_fprintf(STDERR_FILENO, OPEN_PER_SE), NULL);
	*t = (*t)->next;
	while (*t)
	{
		tok = (*t)->content;
		check_par_depth(tok->type, &depth);
		if (depth == 0)
			break ;
		token_node = create_token_node(tok->type, tok->data);
		if (token_node == NULL)
			return (ft_lstclear(&s_sh, free_token), NULL);
		(void)!(ft_lstadd_back(&s_sh, token_node), *t = (*t)->next);
	}
	if (check_after_par(t, &s_sh) == false)
		return (NULL);
	return (s_sh);
}
