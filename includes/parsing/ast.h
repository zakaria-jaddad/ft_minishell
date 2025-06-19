/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:06:52 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/19 08:16:07 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST
# define AST

# include "../../libft/libft.h"
# include "tokenize.h"
# include <stdio.h>
# include <stdbool.h>

typedef struct s_cmd
{
	t_list			*command;
	t_token_type	type;
	struct s_cmd	*left;
	struct s_cmd	*right;
	t_list			*arguments;
}					t_cmd;

t_list				*get_root(t_list *tokens);
t_cmd				*ast(t_list *tokens);

static inline void	print_depth(int depth)
{
	for (int i = 0; i < depth; i++)
		printf("    ");
}

static inline void	print_cmd(t_cmd *root, int depth)
{
	if (root == NULL)
		return ;
	printf("\n");
	print_depth(depth);
	// Print current node
	if (depth == 0)
	{
		printf("root   : ");
	}
	else
	{
		printf("╰───   : ");
	}
	printf("type: %s\n", get_token_type(root->type));
	print_depth(depth + 3);
	printf("command: ");
	fflush(stdout);
	print_tokens(root->command);
	printf("\n");
	print_depth(depth + 3);
	printf("arguments: ");
	fflush(stdout);
	print_tokens(root->arguments);
	printf("\n");
	// if (root->filename != NULL)
	// {
	// 	print_depth(depth + 3);
	// 	printf("filename: ");
	// 	fflush(stdout);
	// 	for (t_list *tmp = root->filename; tmp != NULL; tmp = tmp->next)
	// 	{
	// 		printf("%s", ((t_token *)tmp->content)->data);
	// 		fflush(stdout);
	// 	}
	// 	printf("\n");
	// }
	// printf("\n");
	print_cmd(root->left, depth + 1);
	print_cmd(root->right, depth + 1);
}

#endif // AST_H
