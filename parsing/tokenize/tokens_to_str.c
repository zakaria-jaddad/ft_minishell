#include "../../includes/parsing/parsing.h"

char	*tokens_to_str(t_list *tokens)
{
	t_token	*token;
	char	*rv;
	char	*tmp;

	rv = NULL;
	while (tokens)
	{
		token = tokens->content;
		tmp = ft_strjoin(rv, token->data);
		free(rv);
		rv = tmp;
		tokens = tokens->next;
	}
	return (rv);
}
