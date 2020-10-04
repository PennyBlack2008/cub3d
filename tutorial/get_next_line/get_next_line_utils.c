/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 19:22:14 by jikang            #+#    #+#             */
/*   Updated: 2020/06/08 16:21:50 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int							safer_free(void **pp)
{
	if (pp != NULL && *pp != NULL)
	{
		free(*pp);
		*pp = NULL;
	}
	return (1);
}

size_t						ft_strlen(const char *str)
{
	size_t					i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void						*ft_memmove(void *dest, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*ptr1;
	const unsigned char	*ptr2;

	if (!src && !dest)
		return (NULL);
	ptr1 = (unsigned char*)dest;
	ptr2 = (unsigned char*)src;
	i = 0;
	if (ptr2 < ptr1)
		while (++i <= len)
			ptr1[len - i] = ptr2[len - i];
	else
		while (len-- > 0)
			*(ptr1++) = *(ptr2++);
	return (dest);
}

char						*ft_strdup(const char *string)
{
	size_t					len;
	char					*new;

	len = ft_strlen(string) + 1;
	if (!(new = (char *)malloc(sizeof(char) * len)))
		return (0);
	ft_memmove(new, string, len);
	new[len - 1] = '\0';
	return (new);
}

char						*ft_strjoin(char const *s1, char const *s2)
{
	char					*dest;
	size_t					len1;
	size_t					len2;

	if (s1 && s2)
	{
		len1 = ft_strlen(s1);
		len2 = ft_strlen(s2);
		if (!(dest = malloc(sizeof(char) * (len1 + len2 + 1))))
			return (NULL);
		ft_memmove(dest, s1, len1);
		ft_memmove(dest + len1, s2, len2);
		dest[len1 + len2] = '\0';
		return (dest);
	}
	else
		return (NULL);
}
