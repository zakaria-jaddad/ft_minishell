
#include "../../includes/execution.h"

t_list	*expand(char **args, t_list *envs);

void	print_list(t_list *list)
{
	while (list)
	{
		printf("%s", (char *)list->content);
		list = list->next;
	}
	printf("\n");
}

void	kkkk(void *kk)
{
	return ;
}

int	main(int ac, char **args, char **env)
{
	t_list	*envs;
	t_list	*expanded_list;

	args++;
	envs = envs_init(env);
	expanded_list = expand(args, envs);
	print_list(expanded_list);
	ft_lstclear(&expanded_list, kkkk);
	ft_lstclear(&envs, free_env);
	return (0);
}
