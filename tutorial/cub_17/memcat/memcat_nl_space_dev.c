#define ERROR 0

#include "../../libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

size_t						ft_strlen(const char *str)
{
	size_t					i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void			*ft_memset(void *s, int c, size_t n)
{
	unsigned char *str;

	str = (unsigned char *)s;
	while (n-- > 0)
	{
		*str = (unsigned char)c;
		str++;
	}
	return (s);
}

// 오로지 cub3d 의 map 을 위해 동적 할당 후, space 로 초기화하는 함수
void						*ft_mapalloc(size_t num, size_t size)
{
	void					*new;

	if (!(new = (void *)malloc(size * num)))
		return (NULL);
	ft_memset(new, ' ', num * size);
	return (new);
}

char					*ft_memcat_nl_space(char *dst, char *src, int *width)
{
	char				*str;
	int					len_dst;
	int					i;
	int					j;

	len_dst = ft_strlen(dst);
	if (!(str = (char *)ft_mapalloc(sizeof(char), (len_dst + 1 + *width))))
		return (0);
	i = 0;
	while (dst[i] != '\0')
	{
		str[i] = dst[i];
		i++;
	}
	str[i] = '\n';
	i++;
	j = 0;
	while (src[j] != '\0')
	{
		str[i] = src[j];
		j++;
		i++;
	}
	str[len_dst + 1 + *width] = '\0';
	return (str);
}

int main(void)
{
	char *src = strdup("i am a src");
	char *dst = strdup("i am a dst");
	int	width = 20;

	dst = ft_memcat_nl_space(dst, src, &width);
	printf("%shere\n", dst);
	printf("12345123451234512345\n");

	free (src);
	free (dst);
	return (0);
}
