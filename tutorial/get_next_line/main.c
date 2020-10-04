/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 15:45:55 by jikang            #+#    #+#             */
/*   Updated: 2020/06/06 00:25:34 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int                 		main(void)
{
	int						fd;
	int						status;
	char					*line;

	if((fd = open("test.txt", O_RDONLY)) == -1)
	{
		write(1, "test.txt 파일을 open도중 오류 발생\n", 45);
		return (-1);
	}
	status = 1; // 그저 while문에 들어가기 위한 코드
	while (status == 1)
	{
		status = get_next_line(fd, &line);
		if (status == 1)
		{
			write(1, "\nA line has been read\n", 23);
			if (line == NULL)
				printf("line 얘 일 안하는 데요?");
			printf("line: %s", line);
			free(line);
			printf("\n(라인변경)\n");
		}
		else if (status == 0)
		{
			write(1, "\nEOF has been reached\n", 23);
			printf("%s", line);
			free(line);
		}
		else if (status == -1)
			write(1, "\nAn error occurred\n", 20);
		else
			write(1, "\nsth is wrong\n", 15);
	}
	return (0);
}
// gcc -Wall -Wextra -Werror -D OPEN_MAX=4 -fsanitize=address -g -D BUFFER_SIZE=32 get_next_line.c get_next_line_utils.c main.c
