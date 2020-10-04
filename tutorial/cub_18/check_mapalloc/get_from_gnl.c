#include "../../libft/libft.h"
#include "../../get_next_line/get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define ERROR 0
#define SUCCESS 1
#define FILEEND 0
#define NEXT_WHILE 99
// #define INT_MAX 2147483647

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
	len += cnt * 3;
	return (len);
}

char				*tab2space(char *src, int j)
{
	src[j] = ' ';
	src[j + 1] = ' ';
	src[j + 2] = ' ';
	src[j + 3] = ' ';
	return (src);
}

char				*ft_tab2space(char **line)
{
	char			*str;
	char			*src;
	int				i;
	int				j;

	// 안정적인 프로그램을 위해 src 에 담고 line 은 free 하자
	src = ft_strdup((const char *)*line);
	free(*line);
	line = NULL;

	if (!(str = (char *)malloc(sizeof(char) * (ft_tab2spacelen((const char *)src) + 1))))
		return (ERROR);
	i = 0;
	j = 0;
	while (src[i] != '\0')
	{
		if (src[i] == '\t')
		{
			str = tab2space(str, j);
			j += 3;
		}
		else
			str[j] = src[i];
		j++;
		i++;
	}
	str[j] = '\0';
	free(src);
	src = NULL;
	return (str);
}


// 오로지 cub3d 의 map 을 위해 동적 할당 후, space 로 초기화하는 함수
void						*ft_mapalloc(size_t num, size_t size)
{
	void					*new;

	if (!(new = (void *)malloc(size * num)))
		return (ERROR);
	ft_memset(new, ' ', num * size);
	return (new);
}

char					*ft_memcat_nl_space(char *dst, char *src)
{
	char				*str;
	int					len_dst;
	int					len_src;
	int					i;
	int					j;

	// 이미 가지고 있는 string 의 길이
	len_dst = ft_strlen(dst);
	// src 의 길이
	len_src = ft_strlen(src);
	if (!(str = (char *)ft_mapalloc(sizeof(char), (len_dst + 1 + len_src))))
		return (ERROR);
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
	str[len_dst + 1 + len_src] = '\0';
	return (str);
}

/*
** ft_map_width(char *str)
**	첫 줄로부터 맵의 가로 크기를 얻고 그 숫자를 반환한다.
**	이상하게도 *str[2] 는 seg_fault 이다.
*/

int							ft_map_width(char **str)
{
	char					*line;
	int 					len;
	int						i;

	line = ft_strdup(*str);
	i = 0;		len = 0;

	while (line[i] != '\0')
	{
		if (line[i] == '\t')
			len += 4;
		else
			len++;
		i++;
	}
	return (len);
}

int							main(void)
{
	int						fd;
	int						status;
	char					*line;

	char					**map;
	char					*map_1d;
	int						map_width, map_height;

	int						i, j, k;

	// "example.cub"에 fd 설정하여 get_next_line 으로 parsing 하기
	if((fd = open("example.cub", O_RDONLY)) == -1)
	{
		write(1, "파일을 open도중 오류 발생\n", 45);
		return (ERROR);
	}

	// map_1d 초기화. memcat 에서 seg_fault 방지용
	map_1d = ft_strdup("\0");
	// map_width 초기화. while 문에서 대소비교 fault 방지용
	map_width = 0;
	// map_height 초기화.
	map_height = 0;
	// 첫 줄 받기
	while ((SUCCESS == get_next_line(fd, &line)))
	{
		if (line[0] == '\t' || line[0] == ' ' || line[0] == '1')
		{
			// 0. line 에 있는 \t 을 space 4개로 치환시켜 준다.
			line = ft_tab2space(&line);
			// 1. 첫 번째 line 을 읽은 후, line의 크기를 받아 기존의 map_width 대소비교 후, 큰 값을 map_width 에 삽입.
			if (map_width < ft_strlen(line))
				map_width = ft_strlen(line);
			// 2. 라인을 받을 때마다 map을 map_1d 에 1차원 배열로 담는다.
			map_1d = ft_memcat_nl_space(map_1d, line);
			map_height++;
			free(line);
			line = NULL;
		}
	}

	printf("%s\n", map_1d);
	printf("map_width is %d, map_height is %d\n", map_width, map_height);

	// 여기서 부터 char *map_1d 를 char **map 에 순서대로 알맞게 넣어주는 작업을 하자

	// 일단 한 줄 넣고 확인해볼까?
	// 1. char **map 에 동적할당
	if (!(map = (char **)ft_mapalloc(map_height, sizeof(char *))))
		return (ERROR);
	i = 0;
	while (i < map_height)
	{
		if (!(map[i] = (char *)ft_mapalloc(map_width, sizeof(char))))
			return (ERROR);
		i++;
	}

	// 2. char **map 에 char *map 집어 넣기
	i = 0;		j = 0;		k = 0;
	while (i < map_height && (map_1d[k] != '\0'))
	{
		j = 0;
		while (j < map_width && (map_1d[k] != '\0'))
		{
			if ((map_1d[k] == '\n') && (j == 0))
				map[i][j] = map_1d[++k];
			else if (map_1d[k] == '\n')
			{
				j = INT_MAX;
				k++;
			}
			else
				map[i][j++] = map_1d[k++];
		}
		i++;
	}

	// 3. char **map 출력하여 확인해보기
	i = 0;		j = 0;
	while (i < map_height)
	{
		j = 0;
		while (j < map_width)
		{
			printf("%c", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}

	return (0);
}
