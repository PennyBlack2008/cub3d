#include "cub_21.h"
#define ZERO 0
#define NINETY_DEGREE 90 * M_PI / 180
#define WALL 49 // ascii #1
#define NOT_WALL 48 // ascii #0

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

int					cast_a_ray(t_win *w, t_ray *r)
{
	int x, y;
	double pos_x, pos_y;
	double add_player_x, add_player_y;

	x = 0;
	while (x < WIN_WIDTH * 2)
	{
		y = 0;
		pos_x = x * cos((w->player.ang + r->ang) * -1) + y * sin((w->player.ang + r->ang) * -1);
		pos_y = x * sin((w->player.ang + r->ang) * -1) * -1 + y * cos((w->player.ang + r->ang) * -1);
		add_player_x = pos_x + w->player.x;
		add_player_y = pos_y + w->player.y;
		if (add_player_x >= 0 && add_player_y >= 0)
		{
			// my_mlx_pixel_put(&w->img, add_player_x / 4 + w->mini.plot.x, add_player_y / 4 + w->mini.plot.y, 0xFF0000);
			if (is_wall(add_player_x, add_player_y, w) == WALL)
				break ;
		}
		x++;
	}
	r->x = add_player_x;
	r->y = add_player_y;
	// mlx_put_image_to_window(w->mlx, w->win, w->img.ptr, 0, 0);
	return (0);
}

void				draw_minimap(t_ray *r, t_win *w)
{
	int	i;
	// 미니맵 그리기
	draw_map(w);
	i = 0;
	while (i < w->R_width)
	{
		draw_line((w->player.x / 4) + w->mini.plot.x, (w->player.y / 4) + w->mini.plot.y, (r[i].x / 4) + w->mini.plot.x, (r[i].y / 4) + w->mini.plot.y, 0xFF0000, w);
		i++;
	}
}

int					cast_rays(t_win *w)
{
	t_ray	r[w->R_width];
	int		i;			i = 0;
	double ray_ang;		ray_ang = M_PI / 6;

	while (ray_ang > -1 * M_PI / 6)
	{
		r[i].ang = ray_ang;
		cast_a_ray(w, &(r[i])); // t_ray에 정보 심어주고
		draw_wall(i, &(r[i]), w); // 3D 그려주고
		ray_ang -= M_PI / 3 / 999;
		i++;
	}
	
	// // 미니맵 그리기
	// draw_map(w);
	// i = 0;
	// while (i < w->R_width)
	// {
	// 	draw_line((w->player.x / 4) + w->mini.plot.x, (w->player.y / 4) + w->mini.plot.y, (r[i].x / 4) + w->mini.plot.x, (r[i].y / 4) + w->mini.plot.y, 0xFF0000, w);
	// 	i++;
	// }
	draw_minimap(r, w);
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr, 0, 0);
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
	// mlx_put_image_to_window(w->mlx, w->win, w->img.ptr, 0, 0);
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

	width = w->player.width;

	// 돌리는 건 성공했는 데, 애초에 사각형의 끝점을 중심으로 그렸기 때문에 내가 원하는 공식을 쓸 수가 없다.
	x = width / 2 * -1;
	while (x < width/2)
	{
		y = width / 2 * -1;
		while (y < width/2)
		{
			x_original = x + w->player.x;
			y_original = y + w->player.y;
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