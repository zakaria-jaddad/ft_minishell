#include "../includes/minishell.h"

static int	locate_first_equale(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static char	**get_split_env(char *env)
{
	char	**current_env;
	int		equal_pos;

	current_env = (char **)malloc(sizeof(char *) * 3);
	if (current_env == NULL)
		return (NULL);
	equal_pos = locate_first_equale(env);
	if (equal_pos == -1)
		return (NULL);
	current_env[0] = ft_substr(env, 0, equal_pos);
	if (current_env[0] == NULL)
		return (NULL);
	current_env[1] = ft_substr(env, equal_pos + 1, ft_strlen(env) - equal_pos
			+ 1);
	if (current_env[1] == NULL)
		return (free(current_env[0]), NULL);
	current_env[2] = NULL;
	return (current_env);
}

// TODO: update shell level
static t_list	*simple_env(t_list *env_lst)
{
	char	path_buff[PATH_MAX];

	if (getcwd(path_buff, PATH_MAX) == NULL)
		return (NULL);
	if (append_env(&env_lst, "PWD", path_buff) == NULL)
		return (NULL);
	if (append_env(&env_lst, "SHLVL", "1") == NULL)
		return (clear_envs(&env_lst), NULL);
	if (append_env(&env_lst, "_", "/usr/bin/env") == NULL)
		return (clear_envs(&env_lst), NULL);
	return (env_lst);
}

t_list	*envs_init(char **env)
{
	t_list	*env_lst;
	t_list	*node;
	char	**split_env;
	t_env	*env_content;

	env_lst = NULL;
	if (*env == NULL)
		return (simple_env(env_lst));
	while (*env)
	{
		split_env = get_split_env(*env);
		if (split_env == NULL)
			return (clear_envs(&env_lst), NULL);
		env_content = (t_env *)malloc(sizeof(t_env));
		if (env_content == NULL)
			return (clear_envs(&env_lst), NULL);
		env_content->key = split_env[0];
		env_content->value = split_env[1];
		free(split_env);
		node = ft_lstnew(env_content);
		if (node == NULL)
			return (clear_envs(&env_lst), NULL);
		(ft_lstadd_back(&env_lst, node), env++);
	}
	return (env_lst);
}
