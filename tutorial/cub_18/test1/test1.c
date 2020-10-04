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

int main(void)
{
	char *str = strdup("12345\n12345\n12345");
	char **map;

	int i, j, k;
	i = 0;		j = 0;		k = 0;

	if (!(map = (char **)malloc(sizeof(char *) * (3))))
		return (ERROR);
	while (i < 3)
	{
		if (!(map[i] = (char *)calloc(5, sizeof(char))))
			return (ERROR);
		while (j < 5) // \n 은 다음 *map 으로 넘어가라는 지표가 된다.
		{
			if (str[k] == '\n')
				k++;
			map[i][j] = str[k];

			j++;		k++;
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