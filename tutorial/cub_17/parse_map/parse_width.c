#include "../libft/libft.h"
#include "../get_next_line/get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define ERROR -1
#define SUCCESS 1

/*
** ft_map_width(char *str)
**	첫 줄로부터 맵의 가로 크기를 얻고 그 숫자를 반환한다.
**	이상하게도 *str[2] 는 seg_fault 이다.
**	그래서 line 으로 string 복사 후 코드를 짜니 해결했다.
**	이유는 찾지 못했다.
*/

int							ft_map_width(char **str)
{
	char					*line;
	int 					len;
	int						i;

	line = ft_strdup(*str);
	i = 0;		len = 0;

	printf("야: %s\n", line);
	printf("야0: %c\n", line[0]);
	printf("야1: %c\n", line[1]);
	printf("야2: %c\n", line[2]);
	printf("야3: %c\n", line[3]);
	printf("야4: %c\n", line[4]);

	while (line[i] != '\0')
	{
		if (line[i] == '\t')
			len += 4;
		else
			len++;
		i++;
	}
	printf("그냥 써보는거: %c1, %d\n", line[i], i);
	return (len);
}

int							main(void)
{
	int						fd;
	int						status;
	char					*line;

	char					**map;
	int						map_width;
	int						map_height;

	int						i;
	int						j;

	// "example.cub"에 fd 설정하여 get_next_line 으로 parsing 하기
	if((fd = open("example.cub", O_RDONLY)) == -1)
	{
		write(1, "파일을 open도중 오류 발생\n", 45);
		return (ERROR);
	}

	// 첫 줄 받기
	while ((SUCCESS == get_next_line(fd, &line)))
	{
		if (line[0] == '\t' || line[0] == ' ' || line[0] == 1)
		{
			printf("if 문 여기서: %s\n", line);
			map_width = ft_map_width(&line);
			printf("map의 가로 크기: %d\n", map_width);
			break ;
		}
	}

	return (0);
}