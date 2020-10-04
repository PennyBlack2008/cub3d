/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 18:13:15 by ncolomer          #+#    #+#             */
/*   Updated: 2020/08/12 19:55:19 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// 함수 set_int_in_char 가 하는 역할은?
// 잘 모르겠다.
static void
	set_int_in_char(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8); // 2의 8승
	start[2] = (unsigned char)(value >> 16); // 2의 16승
	start[3] = (unsigned char)(value >> 24); // 2의 24승
}

// bmp_header 를 write 한다.... 무슨 말이지? 일단 fd 를 사용하고, filesize 를 파라미터로 하네.
// 일단 fd 로 받은 어떠한 파일에서 정보를 parsing 후, 구조체 game 에 입력을 하는 건가?
static int
	write_bmp_header(int fd, int filesize, t_game *game)
{
	int				i;
	int				tmp;
	unsigned char	bmpfileheader[54]; // 이건 왜 하필이면 54개의 배열로 했을 까?

	i = 0;
	while (i < 54)
		bmpfileheader[i++] = (unsigned char)(0);
	bmpfileheader[0] = (unsigned char)('B'); // 일단 bmpfileheader 는 {'B', 'M', ...} 이겠구나
	bmpfileheader[1] = (unsigned char)('M');
	set_int_in_char(bmpfileheader + 2, filesize); // int 를 char 에서 세팅한다?
	bmpfileheader[10] = (unsigned char)(54); // 아스키 54: '6'
	bmpfileheader[14] = (unsigned char)(40); // 아스키 40: '('
	tmp = game->window.size.x;
	set_int_in_char(bmpfileheader + 18, tmp);
	tmp = game->window.size.y;
	set_int_in_char(bmpfileheader + 22, tmp);
	bmpfileheader[27] = (unsigned char)(1); // 아스키 1: 'SOH'
	bmpfileheader[28] = (unsigned char)(24); // 아스키 24: 'CAN'
	return (!(write(fd, bmpfileheader, 54) < 0));
}

static int
	get_color(t_window *w, int x, int y)
{
	int	rgb;
	int	color;

	color = *(int*)(w->screen.ptr
			+ (4 * (int)w->size.x * ((int)w->size.y - 1 - y))
			+ (4 * x));
	rgb = (color & 0xFF0000) | (color & 0x00FF00) | (color & 0x0000FF);
	return (rgb);
}

static int
	write_bmp_data(int file, t_window *w, int pad)
{
	const unsigned char	zero[3] = {0, 0, 0};
	int					i;
	int					j;
	int					color;

	i = 0;
	while (i < (int)w->size.y)
	{
		j = 0;
		while (j < (int)w->size.x)
		{
			color = get_color(w, j, i);
			if (write(file, &color, 3) < 0)
				return (0);
			if (pad > 0 && write(file, &zero, pad) < 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

// screenshot 해서 저장하는 함수
int
	save_bmp(t_game *game)
{
	t_window	*w;

	int			filesize;
	int			file;
	int			pad;

	w = &game->window;
	pad = (4 - ((int)w->size.x * 3) % 4) % 4;
	filesize = 54 + (3 * ((int)w->size.x + pad) * (int)w->size.y);
	if ((file = open("screenshot.bmp", O_WRONLY | O_CREAT
									| O_TRUNC | O_APPEND)) < 0)
		return (0);
	if (!write_bmp_header(file, filesize, game))
		return (0);
	if (!write_bmp_data(file, w, pad))
		return (0);
	close(file);
	return (1);
}
