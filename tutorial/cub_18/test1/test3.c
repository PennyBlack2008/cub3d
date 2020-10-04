#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../libft/libft.h"
#include "../../get_next_line/get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define ERROR 0
//#define INT_MAX 2147483647

// 오로지 cub3d 의 map 을 위해 동적 할당 후, space 로 초기화하는 함수
void						*ft_mapalloc(size_t num, size_t size)
{
	void					*new;

	if (!(new = (void *)malloc(size * num)))
		return (ERROR);
	ft_memset(new, 32, num * size);
	return (new);
}

int main(void)
{
	char *str = strdup(" 123\n1 234\n12345");
	char **map;

	int i, j, k;
	i = 0;		j = 0;		k = 0;

	if (!(map = (char **)malloc(sizeof(char *) * (3))))
		return (ERROR);
	while (i < 3 && (str[k] != '\0'))
	{
		if (!(map[i] = (char *)ft_mapalloc(5, sizeof(char))))
			return (ERROR);
		while (j < 5 && (str[k] != '\0')) // \n 은 다음 *map 으로 넘어가라는 지표가 된다.
		{
			if ((str[k] == '\n') && (j == 0))
				map[i][j] = str[++k];
			else if (str[k] == '\n')
			{
				j = INT_MAX;
				k++;
			}
			else
				map[i][j++] = str[k++];
		}
		i++;		j = 0;
	}

	// 출력 하여 확인해보기
	i = 0;		j = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 5)
		{
			printf("map[%d][%d] = %c\t", i, j, map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	return (0);
}