#include "cub_21.h"

void				draw_minimap(t_ray *r, t_win *w)
{
	int	i;
	// 미니맵 그리기
	draw_map(w);
	draw_player(w);
	i = 0;
	while (i < w->R_width)
	{
		draw_line((w->player.x / 4) + w->mini.plot.x, (w->player.y / 4) + w->mini.plot.y, (r[i].x / 4) + w->mini.plot.x, (r[i].y / 4) + w->mini.plot.y, 0xFF0000, w);
		i++;
	}
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
	return (0);
}

int					cast_rays(t_win *w)
{
	t_ray	r[w->R_width];
	int		i;			i = 0;
	double ray_ang;		ray_ang = -1 * M_PI / 6;

	while (ray_ang < M_PI / 6)
	{
		r[i].ang = ray_ang;
		cast_a_ray(w, &(r[i])); // t_ray에 정보 심어주고
		draw_wall(i, &(r[i]), w); // 3D 그려주고
		ray_ang += M_PI / 3 / 999;
		i++;
	}
	// printf("i: %d, r[i - 1] : %f\n", i, r[i - 1].ang * 180 / M_PI);
	draw_minimap(r, w);
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr, 0, 0);
	return (0);
}