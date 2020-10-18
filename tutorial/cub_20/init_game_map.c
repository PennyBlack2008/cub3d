#include "../libft/libft.h"
#include "../get_next_line/get_next_line.h"
#include "cub3d.h"
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

/*
**
** src, dst 는 상위 함수인 map_line 에서 free 및 NULL 처리해줍니다.
*/
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

int							construct_2d_map(t_map *m)
{
	int						i;
	int						j;
	int						k;

	// 1. char **map 에 동적할당
	if (!(m->map = (char **)ft_mapalloc(m->map_height, sizeof(char *))))
		return (ERROR);
	i = 0;
	while (i < m->map_height)
	{
		if (!(m->map[i] = (char *)ft_mapalloc(m->map_width, sizeof(char))))
			return (ERROR);
		i++;
	}

	// 2. char **map 에 char *map 집어 넣기
	i = 0;		j = 0;		k = 0;
	while (i < m->map_height && (m->map_1d[k] != '\0'))
	{
		j = 0;
		while (j < m->map_width && (m->map_1d[k] != '\0'))
		{
			if ((m->map_1d[k] == '\n') && (j == 0))
				m->map[i][j] = m->map_1d[++k];
			else if (m->map_1d[k] == '\n')
			{
				j = INT_MAX;
				k++;
			}
			else
				m->map[i][j++] = m->map_1d[k++];
		}
		i++;
	}
	return (SUCCESS);
}

t_map							*init_struct_map(t_map *m)
{
	if (!(m = malloc(sizeof(t_map))))
		return (ERROR);

	// t_map members
	m->map_width = 0;
	m->map_height = 0;
	m->map_1d = ft_strdup("\0");

	// t_map_info members
	m->info.R_SPEC = 0;
	m->info.R_width = 0;
	m->info.R_height = 0;

	return (m);
}

/*
** parse_resolution_spec(char **str, int *R_width, int *R_height)
** resoulution spec 을 받아오는 함수
*/
int							parse_texture_dir(char **str, char **NO_texture)
{
	char					**arr_by_space;
	int						i;

	arr_by_space = ft_split(*str, ' ');
	i = 0;

	// 에러 처리
	while (arr_by_space[i] != '\0')
		i++;
	if (i < 1)
		return (ERROR);

	*NO_texture = arr_by_space[1];

	free(arr_by_space[0]);
	free(arr_by_space[1]);

	return (SUCCESS);
}

int							map_line(t_map *m, char **line)
{
	char					*copy;
	// 0. line 에 있는 \t 을 space 4개로 치환시켜 준다.
	*line = ft_tab2space(line);

	// 1. 첫 번째 line 을 읽은 후, line의 크기를 받아 기존의 map_width 대소비교 후, 큰 값을 map_width 에 삽입.
	if (m->map_width < ft_strlen(*line))
		m->map_width = ft_strlen(*line);

	// 2. 라인을 받을 때마다 map을 map_1d 에 1차원 배열로 담는다.
	copy = ft_memcat_nl_space(m->map_1d, *line);
	free(m->map_1d);
	m->map_1d = NULL;
	m->map_1d = ft_strdup(copy);
	m->map_height++;
	free(*line);
	*line = NULL;

	// < error 처리 >
	if (m->map_1d == ERROR)
		return (ERROR);
	return (SUCCESS);
}

/*
** parse_rgb_spec(char **str, int *r_spec, int *g_spec, int *b_spec)
** FL, CL 의 rgb spec 을 받아오는 함수
*/
int							parse_rgb_spec(char **str, int *r_spec, int *g_spec, int *b_spec)
{
	char					**arr_by_space;
	char					**arr_by_comma;
	char					*line;
	int						i;

	arr_by_space = ft_split(*str, ' ');
	i = 0;

	// error 처리
	while (arr_by_space[i] != '\0')
		i++;
	if (i < 1)
		return (ERROR);

	arr_by_comma = ft_split(arr_by_space[1], ',');
	i = 0;

	// error 처리
	while (arr_by_comma[i] != '\0')
		i++;
	if (i < 2)
		return (ERROR);
	*r_spec = ft_atoi(arr_by_comma[0]);
	*g_spec = ft_atoi(arr_by_comma[1]);
	*b_spec = ft_atoi(arr_by_comma[2]);

	free(arr_by_comma[0]);
	free(arr_by_comma[1]);
	free(arr_by_comma[2]);

	free(arr_by_space[0]);
	free(arr_by_space[1]);

	return (SUCCESS);
}

/*
** parse_resolution_spec(char **str, int *R_width, int *R_height)
** resoulution spec 을 받아오는 함수
*/
int							parse_resolution_spec(char *str, t_map *m)
{
	char					**arr_by_space;
	int						i;

	arr_by_space = ft_split(str, ' ');
	i = 0;
	while (arr_by_space[i] != '\0')
		i++;
	if (i < 2)
		return (ERROR);
	m->info.R_width = ft_atoi(arr_by_space[1]);
	m->info.R_height = ft_atoi(arr_by_space[2]);
	free(arr_by_space[0]);
	free(arr_by_space[1]);
	free(arr_by_space[2]);

	return (SUCCESS);
}

int							init_game_map(t_map *m)
{
	int						fd;
	int						status;
	char					*line;
	int						i, j, k;

	// "example.cub"에 fd 설정하여 get_next_line 으로 parsing 하기
	if((fd = open("example.cub", O_RDONLY)) == -1)
	{
		write(1, "파일을 open도중 오류 발생\n", 45);
		return (ERROR);
	}

	if (!(m = init_struct_map(m)))
	{
		write(2, "init_strcuct_map error!!\n", 26);
		return (ERROR);
	}

	// char *line 초기화
	line = ft_strdup("\0");

	// 첫 줄 받기
	while ((SUCCESS == get_next_line(fd, &line)))
	{
		if (line[0] == 'R' || line[0] == 'r')
		{
			if (ERROR == parse_resolution_spec(line, m))
			{
				write(2, "Resolution input error\n", 24);
			}
			printf("R_width: %d		R_height: %d\n", m->info.R_width, m->info.R_height);
		}
		else if (line[0] == 'F' || line[0] == 'f')
		{
			if (ERROR == parse_rgb_spec(&line, &m->info.FL_R, &m->info.FL_G, &m->info.FL_B))
			{
				write(2, "Floor input error\n", 19);
			}
			printf("FL_R: %d		FL_G: %d		FL_B: %d\n",m->info.FL_R,m->info.FL_G,m->info.FL_B);
		}
		else if (line[0] == 'C' || line[0] == 'c')
		{
			if (ERROR == parse_rgb_spec(&line, &m->info.CL_R, &m->info.CL_G, &m->info.CL_B))
			{
				write(2, "Ceiling input error\n", 19);
			}
			printf("CL_R: %d		CL_G: %d		CL_B: %d\n",m->info.CL_R,m->info.CL_G,m->info.CL_B);
		}
		else if (line[0] == 'S' && !(line[1] == 'O'))
		{
			if (ERROR == parse_texture_dir(&line, &m->info.sprite_texture))
			{
				write(2, "Sprite texture input error\n", 19);
			}
			printf("Sprite texture dir: %s\n", m->info.sprite_texture);
		}
		else if (line[0] == 'N' && line[1] == 'O')
		{
			if (ERROR == parse_texture_dir(&line, &m->info.NO_texture))
			{
				write(2, "Northern texture input error\n", 19);
			}
			printf("Northern texture dir: %s\n",m->info.NO_texture);
		}
		else if (line[0] == 'S' && line[1] == 'O')
		{
			if (ERROR == parse_texture_dir(&line, &m->info.SO_texture))
			{
				write(2, "Southern texture input error\n", 19);
			}
			printf("Southern texture dir: %s\n",m->info.SO_texture);
		}
		else if (line[0] == 'W' && line[1] == 'E')
		{
			if (ERROR == parse_texture_dir(&line, &m->info.WE_texture))
			{
				write(2, "Western texture input error\n", 19);
			}
			printf("Western texture dir: %s\n",m->info.WE_texture);
		}
		else if (line[0] == 'E' && line[1] == 'A')
		{
			if (ERROR == parse_texture_dir(&line, &m->info.EA_texture))
			{
				write(2, "Eastern texture input error\n", 19);
			}
			printf("Eastern texture dir: %s\n",m->info.EA_texture);
		}
		else if (line[0] == '\t' || line[0] == ' ' || line[0] == '1')
		{
			if (ERROR == map_line(m, &line))
				write(2, "map_line error\n", 16);
		}
		free(line);
		line = NULL;
	}

	// note: 1 차원 맵에 잘 들어갔는 지 확인하려면 주석 해제!
	printf("%s\n", m->map_1d);
	printf("map_width is %d, map_height is %d\n", m->map_width, m->map_height);

	// 여기서 부터 char *map_1d 를 char **map 에 순서대로 알맞게 넣어주는 작업을 하자
	construct_2d_map(m);

	// note: 2 차원 맵이 잘 생성됬는 지 확인하려면 주석 해제!
	i = 0;		j = 0;
	while (i < m->map_height)
	{
		j = 0;
		while (j < m->map_width)
		{
			printf("%c", m->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}

	return (SUCCESS);
}


int							main(void)
{
	t_map					map;

	if (!init_game_map(&map))
	{
		write(1, "init_game_map error!!\n", 23);
		return (ERROR);
	}

	return (0);
}
