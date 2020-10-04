#include "../libft/libft.h"
#include "../get_next_line/get_next_line.h"
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
	char					*num_str_1;
	char					*num_str_2;
	char					*line;
	int						i;

	line = ft_strdup(*str);
	printf("%s\n", line); // R 1920 1080
	printf("line[0]: %c\n", line[0]);
	printf("line[1]: %c\n", line[1]);
	printf("line[2]: %c\n", line[2]);
	printf("line[3]: %c\n", line[3]);
	printf("line[4]: %c\n", line[4]);
	printf("line[5]: %c\n", line[5]);

	// R, 빈칸 뒤에서 부터 읽을 것이므로
	i = 2;

	while (ft_isdigit(line[i]))
		i++;
	line[i] = '\0';
	num_str_1 = ft_strdup(line + 2);
	printf("num_str_1: %s\n", num_str_1);
	*R_width = ft_atoi(num_str_1);
	free(num_str_1);
	num_str_1 = NULL;
	printf("%d\n", *R_width);

	// space 건너 띄기
	num_str_2 = ft_strdup(line + i + 1);
	*R_height = ft_atoi(num_str_2);
	free(num_str_2);
	num_str_2 = NULL;
	printf("%d\n", *R_height);

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
	if((fd = open("example.cub", O_RDONLY)) == -1)
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