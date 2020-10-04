#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../../libft/libft.h"

#define ERROR 0

// 오로지 cub3d 의 map 을 위해 동적 할당 후, space 로 초기화하는 함수
void						*ft_mapalloc(size_t num, size_t size)
{
	void					*new;

	if (!(new = (void *)malloc(size * num)))
		return (ERROR);
	ft_memset(new, ' ', num * size);
	return (new);
}

int							main(void)
{
	char					*str;
	int						i, j;

	if (!(str = ft_mapalloc(11, sizeof(char))))
		return (ERROR);
	i = 0;		j = 0;
	while (i < 3)
	{
		str[i] = i + 48;
		i++;
	}
	str[9] = '1';
	str[10] = '\0';

	while (i <= 8)
	{
		if (str[i] == ' ')
			printf("%d is space\n", i);
		i++;
	}
	printf("%s\n", str);
	return (0);
}