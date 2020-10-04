#include "../../../libft/libft.h"
#include "../../../get_next_line/get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "cub3d.h"

#define ERROR -1
#define SUCCESS 1

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

int							init_struct_map(t_map *m)
{
	if (!(m = malloc(sizeof(t_map))))
		return (ERROR);

	// t_map members
	m->info.R_height = 0;
	m->info.R_width = 0;

	// t_map_info members
	m->info.R_SPEC = 0;
	m->info.R_width = 0;
	m->info.R_height = 0;

	return (SUCCESS);
}


int							main(void)
{
	int						fd;
	int						status;
	char					*line;

	t_map					map;
	int						i;
	int						j;

	// "example.cub"에 fd 설정하여 get_next_line 으로 parsing 하기
	if((fd = open("example.cub", O_RDONLY)) == -1)
	{
		write(1, "파일을 open도중 오류 발생\n", 45);
		return (ERROR);
	}

	if (!init_struct_map(&map))
	{
		write(1, "init_strcuct_map error!!\n", 26);
		return (ERROR);
	}

	// 첫 줄 받기
	while ((SUCCESS == get_next_line(fd, &line)))
	{
		if (line[0] == 'R' || line[0] == 'r')
		{
			if (ERROR == parse_resolution_spec(line, &map))
			{
				write(1, "Resolution input error\n", 24);
			}
			printf("R_width: %d		R_height: %d\n", map.info.R_width, map.info.R_height);
		}
		else if (line[0] == 'F' || line[0] == 'f')
		{
			if (ERROR == parse_rgb_spec(&line, &map.info.FL_R, &map.info.FL_G, &map.info.FL_B))
			{
				write(1, "Floor input error\n", 19);
			}
			printf("FL_R: %d		FL_G: %d		FL_B: %d\n", map.info.FL_R, map.info.FL_G, map.info.FL_B);
		}
		else if (line[0] == 'C' || line[0] == 'c')
		{
			if (ERROR == parse_rgb_spec(&line, &map.info.CL_R, &map.info.CL_G, &map.info.CL_B))
			{
				write(1, "Ceiling input error\n", 19);
			}
			printf("CL_R: %d		CL_G: %d		CL_B: %d\n", map.info.CL_R, map.info.CL_G, map.info.CL_B);
		}
		else if (line[0] == 'N' && line[1] == 'O')
		{
			if (ERROR == parse_texture_dir(&line, &map.info.NO_texture))
			{
				write(1, "Northern texture input error\n", 19);
			}
			printf("Northern texture dir: %s\n", map.info.NO_texture);
		}
		else if (line[0] == 'S' && line[1] == 'O')
		{
			if (ERROR == parse_texture_dir(&line, &map.info.SO_texture))
			{
				write(1, "Southern texture input error\n", 19);
			}
			printf("Southern texture dir: %s\n", map.info.SO_texture);
		}
		else if (line[0] == 'W' && line[1] == 'E')
		{
			if (ERROR == parse_texture_dir(&line, &map.info.WE_texture))
			{
				write(1, "Western texture input error\n", 19);
			}
			printf("Western texture dir: %s\n", map.info.WE_texture);
		}
		else if (line[0] == 'E' && line[1] == 'A')
		{
			if (ERROR == parse_texture_dir(&line, &map.info.EA_texture))
			{
				write(1, "Eastern texture input error\n", 19);
			}
			printf("Eastern texture dir: %s\n", map.info.EA_texture);
		}
	}

	return (0);
}