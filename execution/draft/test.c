#include <stdlib.h>

char	*expand_arr(char **arr, t_list *envs)
{
	int		i;
	char	*tmp;
	char	*res;

	i = 0;
	res = NULL;
	while (arr[i])
	{
		if (arr[i][0] == '$')
		{
			tmp = get_env(envs, arr[i] + 1)->value;
			free(arr[i]);
			arr[i] = tmp;
		}
		tmp = ft_strjoin(res, arr[i]);
		free(res);
		res = tmp;
	}
	return (res);
}
