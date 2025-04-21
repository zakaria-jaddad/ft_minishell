/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:35:35 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/21 15:37:12 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	get_new_line_index(char *s)
{
	int	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i++] == '\n')
			return (i);
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*str;
	size_t	i;
	size_t	j;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	i = 0;
	str = (char *)ft_calloc(1, len_s1 + len_s2 + 1);
	if (str == NULL)
		return (NULL);
	while (i < len_s1 && *s1)
		str[i++] = *s1++;
	j = 0;
	while (j < len_s2 && *s2)
		str[i++] = *s2++;
	return (str);
}

void	join_content(char **content, char *buffer, int n_bytes)
{
	char	*content_place_holder;

	if (content == NULL || buffer == NULL)
		return ;
	buffer[n_bytes] = 0;
	content_place_holder = *content;
	*content = ft_strjoin(content_place_holder, buffer);
	free(buffer);
	free(content_place_holder);
}

char	*read_line(int fd, char *result, int *index)
{
	char	*buffer;
	char	*content;
	int		n_bytes;

	*index = get_new_line_index((content = result));
	if (result && *index)
		return (result);
	while (1)
	{
		if ((size_t)BUFFER_SIZE > INT_MAX)
			return (NULL);
		buffer = (char *)malloc(((size_t)BUFFER_SIZE) + 1);
		if (buffer == NULL)
			return (free(content), NULL);
		n_bytes = read(fd, buffer, BUFFER_SIZE);
		if (n_bytes <= 0)
			return (free((result = NULL, buffer)), content);
		join_content(&content, buffer, n_bytes);
		*index = get_new_line_index(content);
		if (content == NULL || *index)
			break ;
	}
	return (content);
}

char	*ft_gnl(int fd)
{
	static char	*rest[OPEN_MAX];
	char		*buffer;
	char		*line;
	int			i;

	i = 0;
	if (fd < 0 || fd > OPEN_MAX)
		return (NULL);
	if (BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (free(rest[fd]), rest[fd] = NULL);
	buffer = read_line(fd, rest[fd], &i);
	if (buffer == NULL || *buffer == 0)
		return (free(buffer), rest[fd] = NULL);
	rest[fd] = ft_strdup(buffer + i);
	if (!i)
		return (free(rest[fd]), rest[fd] = NULL, buffer);
	line = ft_substr(buffer, 0, i);
	if (line == NULL)
		return (free(buffer), free(rest[fd]), rest[fd] = NULL, buffer = NULL);
	return (free(buffer), line);
}
