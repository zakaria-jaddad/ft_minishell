/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:19:49 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/17 07:23:42 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

// -------- LIBFT --------
int					ft_isdigit(int c);
size_t				ft_strlen(const char *s);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
int					ft_tolower(int c);
char				*ft_strchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
# ifndef ATOIERROR
#  define ATOIERROR 9223372036854775807LL
# endif

long long			ft_atoi(const char *str);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(const char *s1);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				**ft_split(char const *s, char c);
t_list				*ft_split_pro(char *str, char *charset);
t_list				*ft_split_pro_max(char *str, char *charset);
void				*ft_split_free(char **ptr);
char				*ft_itoa(int n);
t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstfirst(t_list *lst);
void				ft_lstadd_front(t_list **lst, t_list *new_node);
void				ft_lstadd_back(t_list **lst, t_list *new_node);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
int					ft_lstsize(t_list *lst);
// -------- LIBFT --------

// -------- FT_FPRINTF --------
size_t				ft_fprintf_strlen(const char *s);
void				ft_fprintf_putnbr_fd(int fd, int n, int *counter);
void				ft_fprintf_put_unsigned_nbr_fd(int fd, unsigned int n,
						int *counter);
void				ft_fprintf_puthex_fd(int fd, size_t n, const char *base,
						int *counter);
void				ft_fprintf_putaddress_fd(int fd, size_t address,
						int *counter);
int					ft_fprintf_putchar_fd(int fd, char c);
int					ft_fprintf_putstr_fd(int fd, char *s);
int					ft_fprintf(int fd, const char *format, ...);
void				ft_lst_rm_one(t_list **head, t_list *node_to_del,
						void clear_content(void *content));
void				ft_add_node(t_list *node_before, t_list *add);
char				*ft_strpbrk(const char *s, const char *accept);

// -------- FT_FPRINTF --------

// -------- FT_GNL --------
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

char				*ft_gnl(int fd);

// -------- FT_GNL --------

#endif
