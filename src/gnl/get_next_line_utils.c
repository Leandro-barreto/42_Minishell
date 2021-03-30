/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lborges- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 11:21:42 by lborges-          #+#    #+#             */
/*   Updated: 2020/02/05 15:05:08 by lborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	n;

	n = 0;
	while (s[n] != '\0')
		n++;
	return (n);
}

char	*ft_strdup(const char *s1)
{
	int		s_len;
	char	*new_s;

	s_len = ft_strlen(s1);
	if (!(new_s = malloc((s_len + 1) * sizeof(char))))
		return (NULL);
	while (s_len >= 0)
	{
		new_s[s_len] = (char)s1[s_len];
		s_len--;
	}
	return (new_s);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		k;
	char	*newstr;
	int		i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	k = ft_strlen(s1) + ft_strlen(s2);
	newstr = (char *)malloc((k + 1) * sizeof(*newstr));
	if (newstr == NULL)
		return (NULL);
	i = 0;
	while (*s1)
	{
		newstr[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		newstr[i] = *s2;
		s2++;
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (*s == c)
		return ((char *)s);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
	{
		substr = (char *)malloc(1);
		if (!substr)
			return (NULL);
		*substr = '\0';
		return (substr);
	}
	substr = (char *)malloc((len + 1) * sizeof(*substr));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
