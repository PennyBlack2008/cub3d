#include "../../libft/libft.h"
#include "../../get_next_line/get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define ERROR -1
#define SUCCESS 1

/*
** parse_resolution_spec(char **str, int *R_width, int *R_height)
** 일단 R의 경우만 생각해서 하자
*/
int							parse_resolution_spec(char **str, int *R_width, int *R_height)
{
	char					**arr_by_space;
	int						i;

	arr_by_space = ft_split(*str, ' ');
	i = 0;
	while (arr_by_space[i] != '\0')
		i++;
	if (i < 2)
		return (ERROR);
	*R_width = ft_atoi(arr_by_space[1]);
	*R_height = ft_atoi(arr_by_space[2]);
	free(arr_by_space[0]);
	free(arr_by_space[1]);
	free(arr_by_space[2]);

	return (SUCCESS);
}

/*
** parse_rgb_spec(char **str, int *r_spec, int *g_spec, int *b_spec)
**
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
	printf("%s\n", arr_by_space[0]); // F
	printf("%s\n", arr_by_space[1]); // 200,100,0
	if (i < 1)
	{
		printf("arr_by_space error\n");
		return (ERROR);
	}
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


int							main(void)
{
	int						fd;
	int						status;
	char					*line;

	// Resolution
	char					*R_SPEC;
	int						R_width;
	int						R_height;
	int						dummy;

	char					*NO_IMG; // North image
	char					*SO_IMG; // South image
	char					*WE_IMG; // West wall image
	char					*EA_IMG; // East wall image

	char					*sprite_img; // sprite image

	// FL RGB
	char					*FL_RGB; // Floor color
	int						FL_R;
	int						FL_G;
	int						FL_B;

	// CL RGB
	char					*CL_RGB; // Ceiling color
	int						CL_R;
	int						CL_G;
	int						CL_B;

	int						i;
	int						j;

	// "jinbkim.cub"에 fd 설정하여 get_next_line 으로 parsing 하기
	if((fd = open("example.cub", O_RDONLY)) == -1)
	{
		write(1, "파일을 open도중 오류 발생\n", 45);
		return (ERROR);
	}

	// 첫 줄 받기
	while ((SUCCESS == get_next_line(fd, &line)))
	{
		if (line[0] == 'R' || line[0] == 'r')
		{
			if (ERROR == parse_resolution_spec(&line, &R_width, &R_height))
			{
				write(1, "Resolution input error\n", 24);
			}
			printf("R_width: %d		R_height: %d\n", R_width, R_height);
		}
		else if (line[0] == 'F' || line[0] == 'f')
		{
			if (ERROR == parse_rgb_spec(&line, &FL_R, &FL_G, &FL_B))
			{
				write(1, "Floor input error\n", 19);
			}
			printf("FL_R: %d		FL_G: %d		FL_B: %d\n", FL_R, FL_G, FL_B);
		}
	}

	return (0);
}