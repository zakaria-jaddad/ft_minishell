/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 03:27:58 by zajaddad          #+#    #+#             */
/*   Updated: 2025/05/01 19:06:46 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	size_t	counter;
	int		word_flag;

	word_flag = 1;
	counter = 0;
	while (*s)
	{
		if (word_flag && *s != c)
		{
			counter++;
			word_flag = 0;
		}
		else if (*s == c)
			word_flag = 1;
		s++;
	}
	return (counter);
}

static char	*get_next_word(char const *s, char c, int index, int *word_length)
{
	int	counter;
	int	word_flag;

	*word_length = 0;
	word_flag = 1;
	counter = 0;
	while (*s)
	{
		if (word_flag && *s != c)
		{
			counter++;
			if (counter == index)
			{
				while (s[*word_length] && s[*word_length] != c)
					(*word_length)++;
				return ((char *) s);
			}
			word_flag = 0;
		}
		else if (*s == c)
			word_flag = 1;
		s++;
	}
	return (NULL);
}

void	*ft_split_free(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	int		word_length;
	int		i;
	char	**ptr;
	char	*word;

	if (s == NULL)
		return (NULL);
	words = count_words(s, c);
	i = 0;
	ptr = (char **) ft_calloc(sizeof(char *), (words + 1));
	if (ptr == NULL)
		return (NULL);
	while (i < words)
	{
		word = get_next_word(s, c, (i + 1), &word_length);
		ptr[i] = (char *) ft_calloc(1, word_length + 1);
		if (ptr[i] == NULL)
			return (ft_split_free(ptr));
		ft_strlcpy(ptr[i++], word, word_length + 1);
	}
	return (ptr);
}
