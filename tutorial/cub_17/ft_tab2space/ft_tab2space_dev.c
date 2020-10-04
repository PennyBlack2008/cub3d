#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

size_t				ft_strlen(const char *str)
{
	size_t			len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

char				*ft_strdup(const char *src)
{
	char			*dst;
	int				i;

	if (!(dst = (char *)malloc(sizeof(char) * (ft_strlen((const char *)src) + 1))))
		return (0);
	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

// only for tab2space, it counts tab as 4 spaces chararector
size_t				ft_tab2spacelen(const char *src)
{
	char			*str;
	size_t			len;
	size_t			cnt; // count tab key

	len = 0;
	cnt = 0;
	str = ft_strdup(src);
	while (str[len] != '\0')
	{
		if (str[len] == '\t')
			cnt++;
		len++;
	}
	printf("cnt number : %zu\n", cnt);
	len += cnt * 3;
	printf("len = %zu\n", len);
	return (len);
}

char				*ft_tab2space(char **line)
{
	char			*str;
	char			*src;
	int				i;
	int				j;

	src = ft_strdup((const char *)*line);
	if (!(str = (char *)malloc(sizeof(char) * (ft_tab2spacelen((const char *)src) + 1))))
		return (0);
	i = 0;
	j = 0;
	while (src[i] != '\0')
	{
		if (src[i] == '\t')
		{
			str[j] = ' ';
			str[j + 1] = ' ';
			str[j + 2] = ' ';
			str[j + 3] = ' ';
			j += 4;
			i++;
		}
		else
		{
			str[j] = src[i];
			i++;
			j++;
		}
	}
	str[j] = '\0';
	return (str);
}

int main(void)
{
	char *line = "\t\t123";
	
	printf("before:%s\n", line);
	line = ft_tab2space(&line);
	printf("after:%s\n", line);
	
	return (0);
}
