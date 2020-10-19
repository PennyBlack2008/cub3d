#include "cub_21.h"
#define ROWS 11
#define COLS 10
#define WALL 49 // ascii #1
#define NOT_WALL 48 // ascii #0

void	map_init(t_win *w)
{
	int i;
	// 여기서 1 은 흰 색, 0 은 검정색이다.
	w->map.map = (char **)malloc(sizeof(char *) * ROWS);
	i = 0;
	while (i < ROWS)
	{
		w->map.map[i] = (char *)malloc(sizeof(char) * COLS);
		i++;
	}
	w->map.map[0] = "1111111111";
	w->map.map[1] = "1000001011";
	w->map.map[2] = "1000100011";
	w->map.map[3] = "1010000011";
	w->map.map[4] = "1010000011";
	w->map.map[5] = "1010000011";
	w->map.map[6] = "1010000011";
	w->map.map[7] = "1010000001";
	w->map.map[8] = "1010000001";
	w->map.map[9] = "1111000111";
	w->map.map[10] = "1111111111";


}

// x는 가로에서 i번 째, y는 세로에서 j번 째
void	draw_rectangle(t_win *w, int x, int y, int color)
{
	int i, j;

	// x, y 는 각각 원점에서 대각선 위치에 있는 점의 x, y 좌표가 된다. x는 사각형의 너비, y는 사각형의 높이
	x *= w->wall.length; // ROWS: 4
	y *= w->wall.length; // COLS: 10
	// printf("x :%d, y: %d \n", x, y);
	// 초기값 x
	i = 0;
	while (i < w->wall.length)
	{
		j = 0;
		while (j < w->wall.length)
		{
			my_mlx_pixel_put(&w->img, (y + i) / 4 + w->mini.plot.x, (x + j) / 4 + w->mini.plot.y, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_win *w)
{
	int i, j;

	i = 0;
	// 가로쪽으로 증가하면서 찍으려면 j < COLS 의 while 문이 먼저 나와야 한다.
	while (i < ROWS)
	{
		j = 0;
		while (j < COLS)
		{
			if (w->map.map[i][j] == '1')
				draw_rectangle(w, i, j, 0xFFFFFF);
			else if (w->map.map[i][j] == '0')
				draw_rectangle(w, i, j, 0x000000);
			j++;
		}
		i++;
	}
}

/*
** int						is_wall(int x, int y, t_win *w)
** 확인하고자 하는 픽셀의 좌표를 넣으면 그 픽셀이 벽인지 확인 해주는 함수, 1이면 벽, 0이면 벽이 아니다.
** 픽셀 좌표 x, y 에 각각 w->wall.length, w->wall.length 를 나누어 이것이 char **map에 어떤 인덱스에
** 속하는 지 알아보고 map[x * w->wall.length][y * w->wall.length]가 0이면 벽이아니고 1이면 벽으로 결정
*/

int			is_wall(double x, double y, t_win *w)
{
	if (w->map.map[(int)(y / w->wall.length)][(int)(x / w->wall.length)] == WALL)
		return (WALL);
	// printf("w->map.map[%d][%d] = %d\n", (int)(y / w->wall.length), (int)(x / w->wall.length), w->map.map[(int)(y / w->wall.length)][(int)(x / w->wall.length)]);
	return (NOT_WALL);
}