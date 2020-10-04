#include "cub_21.h"
#define ROWS 10
#define COLS 10

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
	w->map.map[0] = "1111111111"; //<--------- 여기 문법에서 세그폴트난다.
	w->map.map[1] = "1000001011";
	w->map.map[2] = "1000100011";
	w->map.map[3] = "1010111011";
	w->map.map[4] = "1010011011";
	w->map.map[5] = "1010011011";
	w->map.map[6] = "1010001011";
	w->map.map[7] = "1011100001";
	w->map.map[8] = "1010000001";
	w->map.map[9] = "1111111111";


}

// x는 가로에서 i번 째, y는 세로에서 j번 째
void	draw_rectangle(t_win *w, int x, int y, int color)
{
	int i, j;

	// x, y 는 각각 원점에서 대각선 위치에 있는 점의 x, y 좌표가 된다. x는 사각형의 너비, y는 사각형의 높이
	x *= WIN_HEIGHT / ROWS; // ROWS: 4
	y *= WIN_WIDTH / COLS; // COLS: 10
	// printf("x :%d, y: %d \n", x, y);
	// 초기값 x
	i = 0;
	while (i < WIN_WIDTH / COLS)
	{
		j = 0;
		while (j < WIN_WIDTH / ROWS)
		{
			my_mlx_pixel_put(&w->img, y + i, x + j, color);
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
			// printf("%c\n", w->map.map[i][j]);
			// printf("j: %d\n", j);
			printf("i: %d j: %d\n", i, j);
			if (w->map.map[i][j] == '1')
				draw_rectangle(w, i, j, 0xFFFFFF);
			else if (w->map.map[i][j] == '0')
				draw_rectangle(w, i, j, 0x000000);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr, 0, 0);
}