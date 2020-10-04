#include "../../libft/libft.h"
#include "../../get_next_line/get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define ERROR -1

/*
** parse_num(char *str)
** 일단 R의 경우만 생각해서 하자
*/
int							parse_num(char **str, int *R_width, int *R_height)
{
	char					**arr_by_space;
	char					*num_str_1;
	char					*num_str_2;
	char					*line;
	int						i;
	int						j;

	arr_by_space = ft_split(*str, ' ');
	i = 0;
	while (arr_by_space[i] != '\0')
	{
		printf("arr_by_space[%i]: %s\n", i, arr_by_space[i]);
		i++;
	}
	*R_width = ft_atoi(arr_by_space[1]);
	*R_height = ft_atoi(arr_by_space[2]);
	return (0);
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

	char					*NO_IMG; // North image
	char					*SO_IMG; // South image
	char					*WE_IMG; // West wall image
	char					*EA_IMG; // East wall image

	char					*sprite_img; // sprite image
	char					*FL_RGB; // Floor color
	char					*CL_RGB; // Ceiling color

	int						i;
	int						j;

	// "jinbkim.cub"에 fd 설정하여 get_next_line 으로 parsing 하기
	if((fd = open("../example.cub", O_RDONLY)) == -1)
	{
		write(1, "파일을 open도중 오류 발생\n", 45);
		return (ERROR);
	}

	// 첫 줄 받기
	get_next_line(fd, &line);
	i = 0; j = 0;
	if (line[0] == 'R' || line[0] == 'r')
	{
		if (line[1] == ' ')
		{
			parse_num(&line, &R_width, &R_height);
			printf("R_width: %d		R_height: %d\n", R_width, R_height);
		}
		else
		{
			write(1, "Resolution input error", 23);
			return (ERROR);
		}
	}
	return (0);
}