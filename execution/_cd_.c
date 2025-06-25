/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cd_.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:28:41 by mouait-e          #+#    #+#             */
/*   Updated: 2025/05/23 11:51:20 by mouait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"
#include <unistd.h>

void add_pwd_manual(char *path) {
  int lenth;

  ft_fprintf(STDERR_FILENO,
             "cd: error retrieving current directory: getcwd: cannot access "
             "parent directories: No such file or directory\n");
  lenth = ft_strlen(path);
  if (path[lenth - 1] == '/')
    path[lenth - 1] = '\0';
  manage_pwd(ft_strjoin(manage_pwd(NULL), "/"));
  manage_pwd(ft_strjoin(manage_pwd(NULL), path));
}

int cd_helper(char *path, t_list *list) {
  if (!path || ft_strcmp(path, "") == 0)
    return (1);
  if (chdir(path) < 0) {
    ft_fprintf(2, "shell: cd: %s: No such file or directory\n", path);
    return (1);
  }
  if (get_env(list, "OLDPWD"))
    edit_env(get_env(list, "OLDPWD"), manage_pwd(NULL));
  if (getcwd(NULL, 0)) {
    manage_pwd(getcwd(NULL, 0));
  } else
    add_pwd_manual(path);
  if (get_env(list, "PWD"))
    edit_env(get_env(list, "PWD"), manage_pwd(NULL));
  return (0);
}

int _cd_(t_list *envs, char **args) {
  t_env *env;

  if (!args || !*args) {
    env = get_env(envs, "HOME");
    if (!env) {
      ft_fprintf(STDERR_FILENO, "bash: cd: HOME not set\n");
      return (1);
    }
    if (cd_helper((char *)env->value, envs))
      return (1);
  }
  // else if (args[1])
  // {
  // 	ft_fprintf(STDERR_FILENO, "cd: string not in pwd: %s\n", args[0]);
  // 	return (1);
  // }
  else if (cd_helper(args[0], envs))
    return (1);
  return (0);
}
