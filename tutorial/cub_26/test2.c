#include "cub_21.h"
#define ZERO 0
#define NINETY_DEGREE 90 * M_PI / 180

double				normalize_angle(double ang)
{
	while (ang >= 2 * M_PI)
		ang -= 2 * M_PI;
	while (ang < 0)
		ang += 2 * M_PI;
	return (ang);
}

/*
**	함수 draw_ray 
**	우측 작대기 함수를 약간 변형해서 draw_rays 의 각도를 받아 WIN_WIDTH 의 길이만큼의 광선을 출력하는 함수입니다.
*/

int					draw_ray(t_win *w, double ang)
{
	int x, y;
	double pos_x, pos_y;
	double add_player_x, add_player_y;

	x = 0;
	while (x < WIN_WIDTH / 2)
	{
		y = 0;
		pos_x = x * cos((w->player.ang + ang) * -1) + y * sin((w->player.ang + ang) * -1);
		pos_y = x * sin((w->player.ang + ang) * -1) * -1 + y * cos((w->player.ang + ang) * -1);
		add_player_x = pos_x + w->player.x;
		add_player_y = pos_y + w->player.y;
		if (add_player_x >= 0 && add_player_y >= 0)
		{
			my_mlx_pixel_put(&w->img, add_player_x, add_player_y, 0xFF0000);
			// printf("%d %d\n", round_num_AND_int(add_player_x), round_num_AND_int(add_player_y));
		}
		x++;
	}
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr, 0, 0);
	return (0);
}

int					draw_rays(t_win *w)
{
	double ang;		ang = M_PI / 6;

	while (ang > - M_PI / 6)
	{
		draw_ray(w, ang);
		ang -= 0.01;
	}
	return (0);
}

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
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr, 0, 0);
	return (0);
}

int					round_num_AND_int(double num)
{
	double N;
	int neg;

	N = fabs(num);
	neg = fabs(num) / num;
	if (N - (int)N >= 0.5)
		N = (int)N + 1;
	return (neg * N);
}

int					draw_player(t_win *w)
{
	int width, height;
	int	x, y;
	int x_original, y_original;
	double pos_x, pos_y;
	double add_player_x, add_player_y;

	width = 30;
	height = 30;

	// 돌리는 건 성공했는 데, 애초에 사각형의 끝점을 중심으로 그렸기 때문에 내가 원하는 공식을 쓸 수가 없다.
	x = width / 2 * -1;
	while (x < width/2)
	{
		y = height / 2 * -1;
		while (y < height/2)
		{
			x_original = x + w->player.x;
			y_original = y + w->player.y;
			pos_x = x * cos(w->player.ang * -1) + y * sin(w->player.ang * -1);
			pos_y = x * sin(w->player.ang * -1) * -1 + y * cos(w->player.ang * -1);
			add_player_x = pos_x + w->player.x;
			add_player_y = pos_y + w->player.y;
			if (add_player_x >= 0 && add_player_y >= 0)
			{
				my_mlx_pixel_put(&w->img, add_player_x, add_player_y, 0xbbccff);
				// printf("%d %d\n", round_num_AND_int(add_player_x), round_num_AND_int(add_player_y));
			}
			y++;
		}
		x++;
	}
	// 정면 작대기
	x = 0;
	while (x < width / 2 + 30)
	{
		y = 0;
		pos_x = x * cos(w->player.ang * -1) + y * sin(w->player.ang * -1);
		pos_y = x * sin(w->player.ang * -1) * -1 + y * cos(w->player.ang * -1);
		add_player_x = pos_x + w->player.x;
		add_player_y = pos_y + w->player.y;
		if (add_player_x >= 0 && add_player_y >= 0)
		{
			my_mlx_pixel_put(&w->img, add_player_x, add_player_y, 0xFF0000);
			// printf("%d %d\n", round_num_AND_int(add_player_x), round_num_AND_int(add_player_y));
		}
		x++;
	}

	// 우측 작대기
	y = 0;
	while (y < height / 2 + 30)
	{
		x = 0;
		pos_x = x * cos(w->player.ang * -1) + y * sin(w->player.ang * -1);
		pos_y = x * sin(w->player.ang * -1) * -1 + y * cos(w->player.ang * -1);
		add_player_x = pos_x + w->player.x;
		add_player_y = pos_y + w->player.y;
		if (add_player_x >= 0 && add_player_y >= 0)
		{
			my_mlx_pixel_put(&w->img, add_player_x, add_player_y, 0x0000FF);
			// printf("%d %d\n", round_num_AND_int(add_player_x), round_num_AND_int(add_player_y));
		}
		y++;
	}	

	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr, 0, 0);

	return (0);
}


int					draw_grid(t_win *w)
{
	int x, y;

	x = 0;	y = WIN_HEIGHT / 2;
	while (x < WIN_WIDTH)
	{
		my_mlx_pixel_put(&w->img, x, y, 0x00ccff);
		x++;
	}

	y = 0;	x = WIN_WIDTH / 2;
	while (y < WIN_HEIGHT)
	{
		my_mlx_pixel_put(&w->img, x, y, 0x00ccff);
		y++;
	}
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr, 0, 0);

	return (0);
}