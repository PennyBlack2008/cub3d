#include "cub_21.h"

double				normalize_angle(double ang)
{
	while (ang >= 2 * M_PI)
		ang -= 2 * M_PI;
	while (ang < 0)
		ang += 2 * M_PI;
	return (ang);
}

void				set_plot_int(t_plot *plot, int x, int y)
{
	plot->x = x;
	plot->y = y;
}

void				draw_minimap(t_ray *r, t_win *w)
{
	int	i;
	t_plot player;
	t_plot ray;
	// 미니맵 그리기
	draw_map(w);
	draw_player(w);
	set_plot_int(&player, (w->player.x / 4) + w->mini.plot.x, (w->player.y / 4) + w->mini.plot.y);
	i = 0;
	while (i < w->R_width)
	{
		set_plot_int(&ray, (r[i].hit.x / 4) + w->mini.plot.x, (r[i].hit.y / 4) + w->mini.plot.y);
		draw_line(player, ray, 0xFF0000, w);
		i++;
	}
}

/*
**	함수 draw_ray
**	우측 작대기 함수를 약간 변형해서 draw_rays 의 각도를 받아 WIN_WIDTH 의 길이만큼의 광선을 출력하는 함수입니다.
**	plot은 (0, 0) 의 픽셀에서 각도를 변환하며 계산한 좌표이고, plot_player는 플레이어의 현재위치를 더한 좌표 값입니다.
*/

int					draw_a_ray(t_ray *r, t_win *w)
{
	int x, y;
	t_plot plot;
	t_plot plot_player;

	x = 0;
	while (x < WIN_WIDTH * 2)
	{
		y = 0;
		plot.x = x * cos(r->ang * -1) + y * sin(r->ang * -1);
		plot.y = x * sin(r->ang * -1) * -1 + y * cos(r->ang * -1);
		plot_player.x = plot.x + w->player.x;
		plot_player.y = plot.y + w->player.y;
		if (plot_player.x >= 0 && plot_player.y >= 0)
		{
			// my_mlx_pixel_put(&w->img, (plot_player.x / 4) + w->mini.plot.x, (plot_player.y / 4) + w->mini.plot.y, 0xFF0000);
			if (is_wall(plot_player.x, plot_player.y, w) == WALL)
				break ;
		}
		x++;
	}
	r->hit.x = plot_player.x;
	r->hit.y = plot_player.y;
	return (0);
}

int					draw_rays(t_win *w)
{
	t_ray		r[w->R_width];
	int			i;				i = 0;
	double		ray_ang;		ray_ang = -1 * w->fov_ang / 2;

	while (ray_ang < w->fov_ang / 2)
	{
		r[i].ang = normalize_angle(w->player.ang + ray_ang);
		draw_a_ray(&(r[i]), w);
		draw_a_wall(i, &(r[i]), w);
		draw_ceiling(i, &(r[i]), w);
		draw_floor(i, &(r[i]), w);
		ray_ang += w->fov_ang / (w->R_width - 1);
		i++;
	}
	draw_minimap(r, w);
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr, 0, 0);
	return (0);
}

/*
** draw_background 함수는 검정화면을 출력하기 위한 함수입니다. 이 함수가 있어서 플레이어가 움직일 때, 움직이기 전의 위치의 픽셀을 까맣게 지워줍니다.
*/

int					draw_background(t_win *w)
{
	int				x,y;

	x = 0;
	while (x < w->R_width)
	{
		x++;
		y = 0;
		while (y < w->R_height)
		{
			my_mlx_pixel_put(&w->img, x, y, 0x000000);
			y++;
		}
	}
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr, 0, 0);
	return (0);
}

int					draw_player(t_win *w)
{
	int width, height;
	int	x, y;
	t_plot	plot;
	t_plot	plot_player;
	
	width = w->player.width;
	height = w->player.width;

	// 돌리는 건 성공했는 데, 애초에 사각형의 끝점을 중심으로 그렸기 때문에 내가 원하는 공식을 쓸 수가 없다.
	x = width / 2 * -1;
	while (x < width/2)
	{
		y = width / 2 * -1;
		while (y < width / 2)
		{
			plot.x = x * cos(w->player.ang * -1) + y * sin(w->player.ang * -1);
			plot.y = x * sin(w->player.ang * -1) * -1 + y * cos(w->player.ang * -1);
			plot_player.x = plot.x + w->player.x;
			plot_player.y = plot.y + w->player.y;
			if (plot_player.x >= 0 && plot_player.y >= 0)
			{
				my_mlx_pixel_put(&w->img, plot_player.x / 4 + w->mini.plot.x, plot_player.y / 4 + w->mini.plot.y, 0xbbccff);
				// printf("%d %d\n", round_num_AND_int(plot_player.x), round_num_AND_int(plot_player.y));
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
		plot.x = x * cos(w->player.ang * -1) + y * sin(w->player.ang * -1);
		plot.y = x * sin(w->player.ang * -1) * -1 + y * cos(w->player.ang * -1);
		plot_player.x = plot.x + w->player.x;
		plot_player.y = plot.y + w->player.y;
		if (plot_player.x >= 0 && plot_player.y >= 0)
		{
			my_mlx_pixel_put(&w->img, plot_player.x / 4 + w->mini.plot.x, plot_player.y / 4 + w->mini.plot.y, 0xFF0000);
			// printf("%d %d\n", round_num_AND_int(plot_player.x), round_num_AND_int(plot_player.y));
		}
		x++;
	}

	// 우측 작대기
	y = 0;
	while (y < height / 2 + 30)
	{
		x = 0;
		plot.x = x * cos(w->player.ang * -1) + y * sin(w->player.ang * -1);
		plot.y = x * sin(w->player.ang * -1) * -1 + y * cos(w->player.ang * -1);
		plot_player.x = plot.x + w->player.x;
		plot_player.y = plot.y + w->player.y;
		if (plot_player.x >= 0 && plot_player.y >= 0)
		{
			my_mlx_pixel_put(&w->img, plot_player.x / 4 + w->mini.plot.x, plot_player.y / 4 + w->mini.plot.y, 0x0000FF);
			// printf("%d %d\n", round_num_AND_int(plot_player.x), round_num_AND_int(plot_player.y));
		}
		y++;
	}

	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr, 0, 0);

	return (0);
}

/*
** draw_grid 는 디버깅할 때 편하려고 해상도의 가로길이와 세로길이의 반을 통과하는 선을 그리는 함수입니다.
*/

int					draw_grid(t_win *w)
{
	int x, y;

	x = 0;	y = w->R_height / 2;
	while (x < w->R_width)
	{
		my_mlx_pixel_put(&w->img, x, y, 0x00ccff);
		x++;
	}

	y = 0;	x = w->R_width / 2;
	while (y < w->R_height)
	{
		my_mlx_pixel_put(&w->img, x, y, 0x00ccff);
		y++;
	}
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr, 0, 0);

	return (0);
}