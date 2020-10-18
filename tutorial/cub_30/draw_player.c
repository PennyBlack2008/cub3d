#include "cub_21.h"

int					draw_background(t_win *w)
{
	int				x,y;

	x = 0;
	while (x < WIN_WIDTH)
	{
		x++;
		y = 0;
		while (y < WIN_HEIGHT)
		{
			my_mlx_pixel_put(&w->img, x, y, 0x000000);
			y++;
		}
	}
	return (0);
}

int					draw_player(t_win *w)
{
	int width;
	int	x, y;
	double pos_x, pos_y;
	double add_player_x, add_player_y;

	width = w->player.width;

	// 돌리는 건 성공했는 데, 애초에 사각형의 끝점을 중심으로 그렸기 때문에 내가 원하는 공식을 쓸 수가 없다.
	x = width / 2 * -1;
	while (x < width / 2)
	{
		y = width / 2 * -1;
		while (y < width / 2)
		{
			pos_x = x * cos(w->player.ang * -1) + y * sin(w->player.ang * -1);
			pos_y = x * sin(w->player.ang * -1) * -1 + y * cos(w->player.ang * -1);
			add_player_x = pos_x + w->player.x;
			add_player_y = pos_y + w->player.y;
			if (add_player_x >= 0 && add_player_y >= 0)
			{
				my_mlx_pixel_put(&w->img, add_player_x / 4 + w->mini.plot.x, add_player_y / 4 + w->mini.plot.x, 0xbbccff);
				// printf("%d %d\n", round_num_AND_int(add_player_x), round_num_AND_int(add_player_y));
			}
			y++;
		}
		x++;
	}
	return (0);
}