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

void handel_args(int *i, int *nl, char **args) {
  int j;

  while (args[*i]) {
    j = 0;
    if (args[*i][j++] == '-')
      while (args[*i][j] == 'n')
        j++;
    if (!args[*i][j] && j > 1)
      *nl += 1;
    else
      break;
    *i += 1;
  }
}

int _echo_(char **args) {
  int i;
  int nl;

  nl = 0;
  if (!args || !*args) {
    write(STDOUT_FILENO, "\n", 1);
    return (1);
  }
  i = 0;
  while (args[i]) {
    if (args[i])
      ft_fprintf(STDOUT_FILENO, "%s", args[i]);
    if (args[++i])
      ft_fprintf(STDOUT_FILENO, "%s", " ");
  }
  if (!nl || !args[0])
    ft_fprintf(STDOUT_FILENO, "\n");
  free_double_pointer((void **)args);
  return (0);
}
