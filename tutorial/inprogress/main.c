#include "cub_21.h"

#define ERROR 0
#define SUCCESS 1
#define FILEEND 0

int main()
{
	int						fd;
	int						status;
	char					*line;
	int						i, j, k;

	// "example.cub"에 fd 설정하여 get_next_line 으로 parsing 하기
	if((fd = open("image/eagle.xpm", O_RDONLY)) == -1)
	{
		write(1, "파일을 open도중 오류 발생\n", 45);
		return (ERROR);
	}

	// line 초기화
	line = ft_strdup("\0");

	// gnl 로 받아오기)
	while ((SUCCESS == get_next_line(fd, &line)))
	{
		if (ft_memcmp(line, "/* XPM */", ft_strlen(line)) != 0)
		{
			printf("xpm format is wrong\n");
			break ;
		}
		else if (ft_memcmp(line, "/* XPM */", ft_strlen(line)) == 0)
		{
			printf("this is xpm format\n");
			break ;
		}

		free(line);
		line = NULL;
	}
	free(line);
	line = NULL;

	return (0);
}