/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pro_max.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 03:27:58 by zajaddad          #+#    #+#             */
/*   Updated: 2025/05/14 16:15:35 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strchar(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	if (c == charset[i])
		return (1);
	return (0);
}

static int	ft_count_words(char *str, char *charset)
{
	int	flag;
	int	i;
	int	counter;

	i = 0;
	flag = 1;
	counter = 0;
	while (str[i])
	{
		if (ft_strchar(str[i], charset) == 0 && flag == 1)
		{
			counter++;
			flag = 0;
		}
		else if (ft_strchar(str[i], charset) == 1)
			flag = 1;
		else
			flag = 0;
		i++;
	}
	return (counter);
}

static char	*ft_get_current_word(int index, char *str, char *charset)
{
	int	flag;
	int	i;
	int	counter;

	i = 0;
	flag = 1;
	counter = 0;
	while (str[i] && index != 1)
	{
		if (ft_strchar(str[i], charset) == 0 && flag == 1)
		{
			counter++;
			if (counter == index)
				return (&str[i]);
			flag = 0;
		}
		else if (ft_strchar(str[i], charset) == 1)
			flag = 1;
		else
			flag = 0;
		i++;
	}
	return (str);
}

static void	ft_strcpy(char *dest, char *src, char *charset)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (ft_strchar(src[i], charset) == 1)
		i++;
	while (src[i])
	{
		if (ft_strchar(src[i], charset) == 1)
			break ;
		dest[j++] = src[i];
		i++;
	}
	dest[j] = '\0';
}

char	**ft_split_pro_max(char *str, char *charset)
{
	char	**double_ptr;
	char	*word;
	int		word_length;
	int		i;

	i = 0;
	word_length = ft_count_words(str, charset);
	double_ptr = (char **) malloc((sizeof(char *) * word_length) + 1);
	if (double_ptr == NULL)
		return (NULL);
	while (i < word_length)
	{
		double_ptr[i] = (char *) malloc(sizeof(char) * 120000);
		if (double_ptr[i] == NULL)
			return (ft_split_free(double_ptr));
		word = ft_get_current_word((i + 1), str, charset);
		ft_strcpy(double_ptr[i++], word, charset);
	}
	double_ptr[i] = 0;
	return (double_ptr);
}
