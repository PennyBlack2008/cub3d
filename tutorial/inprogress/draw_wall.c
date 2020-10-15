#include "cub_21.h"

/*
** draw_wall
** https://permadi.com/1996/05/ray-casting-tutorial-9/
**
** projected wall height / distance of player to projected plane = actual wall height / distance of player to the wall
** 
** projected wall height = actual wall height * distance of player to projected plane / distance of player to the wall
** 1. actual wall height 는 cub_21.c 의 w->wall.height = 800; 에서 정의됨
** 2. distance of player to projected plane 은 cub_21.c 에서 화면의 해상도 크기 / 2 * atan(fov) 로 정의됨. w->player.projected_plane = w->R_width / 2 * atan(M_PI_2 / 3);
** 3. distance of player to the wall 은 ray 에서 벽에 부딛힌 좌표를 찾고 그 좌표와 플레이어의 좌표를 빗변계산하여 정의됨
** 4. 위의 세가지 요소와 공식을 통해 projected wall height 를 구하고 그 크기만큼 순서대로 직선을 그림
**
*/

double				get_which_wall(t_ray *r, t_win *w)
{
	double			x;

	if (r->ang > M_PI_4 * 7 || r->ang < M_PI_4)
	{
		r->wall_NSEW = EAST;
		x = r->wall.y - r->y;
	}
	else if (r->ang > M_PI_4 && r->ang < M_PI_4 * 3)
	{
		r->wall_NSEW = SOUTH;
		x = r->x - r->wall.x;
	}
	else if (r->ang > M_PI_4 * 3 && r->ang < M_PI_4 * 5)
	{
		r->wall_NSEW = WEST;
		x = r->wall.y - r->y;
	}
	else if (r->ang > M_PI_4 * 5 && r->ang < M_PI_4 * 7)
	{
		r->wall_NSEW = NORTH;
		x = r->x - r->wall.x;
	}
	return (x);
}
int					get_color_tex(double x, double y, double scale, t_ray *r, t_win *w)
{
	int				color;
	double			px, py;

	x = get_which_wall(r, w); // 여기서 x 에 넣어줄 값을 정한다.
	px = floor(x / scale);
	py = floor(y / scale);
	color = w->curr_tex[(int)(64 * py + px)];
	return (color);
}

void		draw_wall(int i, t_ray *r, t_win *w)
{
	double dist_to_wall;
	double pjtd_height;
	int color;
	double scale;

	dist_to_wall = hypot(r->x - w->player.x, r->y - w->player.y) * cos(r->ang);
	pjtd_height = w->wall.height * w->player.projected_plane / dist_to_wall;
	if (pjtd_height > w->R_height)
		pjtd_height = w->R_height;
	scale = pjtd_height / 64;
	int j;		j = 0;		int k;		k = pjtd_height / 2 - 1;

	r->ceiling = 500 - k;
	
	// 중간인 500 은 j while 에서 처리
	while (j < pjtd_height / 2) // 벽을 아래로 내리기
	{
		// j 는 어떻게 처리할 것인가? pjtd_height 를 조절하면서 구해야한다.
		color = get_color_tex(i, j + (pjtd_height / 2), scale, r, w);
		my_mlx_pixel_put(&w->img, i, 500 + j, color);
		j++;
	}
	while (k > 0) // 벽을 위로 올리기
	{
		color = get_color_tex(i, k, scale, r, w);
		my_mlx_pixel_put(&w->img, i, 500 - k, color);
		k--;
	}
	r->floor = 500 + j;
}

void		draw_ceiling(int i, t_ray *r, t_win *w)
{
	int		j;

	j = r->ceiling;
	while (j >= 0)
	{
		my_mlx_pixel_put(&w->img, i, j, 0xff0000);
		j--;
	}
}

void		draw_floor(int i, t_ray *r, t_win *w)
{
	int		j;

	j = r->floor;
	while (j <= w->R_height)
	{
		my_mlx_pixel_put(&w->img, i, j, 0x0000ff);
		j++;
	}
}