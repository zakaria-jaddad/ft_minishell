/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _echo_.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:26:10 by mouait-e          #+#    #+#             */
/*   Updated: 2025/05/23 12:15:01 by mouait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"
#include <unistd.h>

int _echo_(char **args) {
  int i;

  if (!args || !*args) {
    write(STDOUT_FILENO, "\n", 1);
    return (1);
  }
  i = 0;
  if (ft_strncmp(args[0], "-n", ft_strlen(args[0])) == 0)
    i++;
  while (args[i]) {
    if (args[i])
      ft_fprintf(STDOUT_FILENO, "%s", args[i]);
    if (args[++i])
      ft_fprintf(STDOUT_FILENO, "%s", " ");
  }
  if (ft_strncmp(args[0], "-n", ft_strlen(args[0])) != 0 || !args[0])
    ft_fprintf(STDOUT_FILENO, "\n");
  free_double_pointer((void **)args);
  return (0);
}
