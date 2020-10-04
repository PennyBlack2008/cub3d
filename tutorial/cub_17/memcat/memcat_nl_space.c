#define ERROR 0

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

size_t					ft_strlen(char *str)
{
	size_t				len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

char					*ft_memcat_nl_space(char *dst, char *src, int *width)
{
	char				*str;
	int					len_dst;
	int					len_src;
	int					i;
	int					j;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (!(str = (char *)malloc(sizeof(char) * (len_dst + 1 + *width))))
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
	while (*width - j > 0)
	{
		str[i] = ' ';
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}


int main(void)
{
	char *src = strdup("i am a src");
	char *dst = strdup("i am a dst");
	int	width = 20;

	dst = ft_memcat_nl_space(dst, src, &width);
	printf("%shere\n", dst);

	free (src);
	free (dst);
	return (0);
}
