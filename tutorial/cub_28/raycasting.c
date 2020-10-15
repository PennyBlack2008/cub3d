#include "cub_28.h"

double					normalize_angle(double ang)
{
	while (ang >= 2 * M_PI)
		ang -= 2 * M_PI;
	while (ang < 0)
		ang += 2 * M_PI;
	return (ang);
}

void		restrain_plot(t_plot *plot, t_win *w)
{
	if (plot->x < 0)
		plot->x = 0;
	if (plot->x > w->R_width)
		plot->x = w->R_width - 1;
	if (plot->y < 0)
		plot->y = 0;
	if (plot->y > w->R_height)
		plot->y = w->R_height - 1;
}

void		restrain_length(double *length, t_win *w)
{
	if (*length < 0)
		*length = 0;
	if (*length > w->R_width)
		*length = w->R_width - 1;
	if (*length < 0)
		*length = 0;
	if (*length > w->R_height)
		*length = w->R_height - 1;
}

t_plot		set_plot(double x, double y)
{
	t_plot	plot;

	plot.x = x;
	plot.y = y;
	return (plot);
}

// 빨간 광선
t_plot		cast_horz_ray(t_ray *r, t_win *w)
{
	t_plot	A; // intercept

	/*
	** 광선이 벽과 만나는 최초위치는 벽의 좌표와 광선의 각도를 계산해 A.y 를 구할 수 있다.
	** A.y 광선 각도가 위일 때 if, 광선 각도가 밑일 때가 else 로 계산하였음
	** 플레이어의 위치에 TILE의 길이를 나누어, 나누어 떨어지는 값이 A.y 가 된다.
	*/

	if (M_PI <= r->ang && r->ang < 2 * M_PI)
		A.y = floor(w->player.y / TILE_LENGTH) * TILE_LENGTH;
	else
		A.y = floor(w->player.y / TILE_LENGTH) * (TILE_LENGTH + 1);

	if (w->player.y == A.y || r->ang == M_PI_2 || r->ang == M_PI_2 * 3)
		A.x = w->player.x;
	else if ((0 < r->ang && r->ang < M_PI_2) || (M_PI < r->ang && r->ang < M_PI_2 * 3)) // 0 도, 180도 일 때는 horzhit 하지 못한다.
		A.x = w->player.x + (A.y - w->player.y) / tan(r->ang);
	else if ((M_PI_2 < r->ang && r->ang < M_PI) || (M_PI_2 * 3 < r->ang && r->ang < M_PI * 2))
		A.x = w->player.x - (A.y - w->player.y) / tan(r->ang);

	printf("intercept A(%f, %f)\n", A.x, A.y);
	double	Xa;
	double	Ya;
	Ya = TILE_LENGTH;
	Xa = fabs(Ya / tan(2 * M_PI - r->ang));
	restrain_length(&Xa, w);

	while (is_wall_ray(A.x, A.y, r, w) == NOT_WALL && A.x < w->R_width && A.y < w->R_height && A.x > 0 && A.y > 0)
	{
		if (0 == r->ang)
		{
			A.x += Xa;
		}
		else if (0 < r->ang && r->ang < M_PI_2)
		{
			A.x += Xa;
			A.y += Ya;
		}
		else if (M_PI_2 == r->ang)
		{
			A.y += Ya;
		}
		else if (M_PI_2 < r->ang && r->ang < M_PI)
		{
			A.x -= Xa;
			A.y += Ya;
		}
		else if (M_PI == r->ang)
		{
			A.x -= Xa;
		}
		else if (M_PI < r->ang && r->ang < M_PI_2 * 3)
		{
			A.x -= Xa;
			A.y -= Ya;
		}
		else if (M_PI_2 * 3 == r->ang)
		{
			A.y -= Ya;
		}
		else if (M_PI_2 * 3 < r->ang && r->ang < 2 * M_PI)
		{
			A.x += Xa;
			A.y -= Ya;
		}
	}
	printf("결정된 점 A(%f, %f), ang: %f\n", A.x, A.y, r->ang * 180 / M_PI);
	return (A);
}

// 초록 광선
t_plot		cast_vert_ray(t_ray *r, t_win *w)
{
	t_plot	B; // intercept

	/*
	** 광선이 벽과 만나는 최초위치는 벽의 좌표와 광선의 각도를 계산해 B.x 를 구할 수 있다.
	** B.x 광선 각도가 위일 때 if, 광선 각도가 밑일 때가 else 로 계산하였음
	** 플레이어의 위치에 TILE의 길이를 나누어, 나누어 떨어지는 값이 B.x 가 된다.
	*/

	if ((M_PI_2 <= r->ang && r->ang < M_PI_2 * 3) || w->player.x % TILE_LENGTH == 0)
		B.x = floor(w->player.x / TILE_LENGTH) * TILE_LENGTH;
	else
		B.x = floor(w->player.x / TILE_LENGTH) * (TILE_LENGTH + 1);

	// intercept 좌표인 B의 x 좌표가 타일에 걸렸을 때의 좌표이므로 그 때가 vert ray의 좌표가 된다.
	if (w->player.x == B.x || r->ang == 0 || r->ang == M_PI)
		B.y = w->player.y;
	else if ((0 < r->ang && r->ang < M_PI_2) || (M_PI < r->ang && r->ang < M_PI_2 * 3)) // 90도, 270도 일 때는 verthit 하지 못한다.
		B.y = w->player.y + tan(r->ang) * (B.x - w->player.x);
	else if ((M_PI_2 < r->ang && r->ang < M_PI) || (M_PI_2 * 3 < r->ang && r->ang < M_PI * 2))
		B.y = w->player.y - tan(r->ang) * (B.x - w->player.x);

	double Xb;
	double Yb;

	Xb = TILE_LENGTH;
	Yb = fabs(TILE_LENGTH * tan(2 * M_PI - r->ang));
	restrain_length(&Yb, w);

	while(is_wall_ray(B.x, B.y, r, w) == NOT_WALL && B.x < w->R_width && B.y < w->R_height && B.x > 0 && B.y > 0)
	{
		if (0 == r->ang)
		{
			B.x += Xb;
		}
		else if (0 < r->ang && r->ang < M_PI_2)
		{
			B.x += Xb;
			B.y += Yb;
		}
		else if (r->ang == M_PI_2)
		{
			B.y += Yb;
		}
		else if (M_PI_2 < r->ang && r->ang < M_PI)
		{
			B.x -= Xb;
			B.y += Yb;
		}
		else if (r->ang == M_PI)
		{
			B.x -= Xb;
		}
		else if (M_PI < r->ang && r->ang < M_PI_2 * 3)
		{
			B.x -= Xb;
			B.y -= Yb;
		}
		else if (r->ang == M_PI_2 * 3)
		{
			B.y += Yb;
		}
		else if (M_PI_2 * 3 < r->ang && r->ang < 2 * M_PI)
		{
			B.x += Xb;
			B.y -= Yb;
		}
	}
	printf("결정된 점 B(%f, %f), 각도: %f\n", B.x, B.y, r->ang * 180 / M_PI);
	return (B);
}

void		draw_ray(t_ray *r, t_win *w)
{
	t_plot	hit_horz;
	t_plot	hit_vert;
	double	dist_horz;
	double	dist_vert;

	hit_horz = cast_horz_ray(r, w);
	hit_vert = cast_vert_ray(r, w);
	restrain_plot(&hit_horz, w);
	restrain_plot(&hit_vert, w);
	dist_horz = hypot((double)w->player.x - hit_horz.x, (double)w->player.y - hit_horz.y);
	dist_vert = hypot((double)w->player.x - hit_vert.x, (double)w->player.y - hit_vert.y);

	// draw_line(w->player.x, w->player.y, (int)hit_horz.x, (int)hit_horz.y, 0xFF0000, w);
	// draw_line(w->player.x, w->player.y, (int)hit_vert.x, (int)hit_vert.y, 0x00FF00, w);
	// 가장 벽에 가까운 좌표로
	if (dist_horz < dist_vert)
	{
		draw_line(w->player.x, w->player.y, (int)hit_horz.x, (int)hit_horz.y, 0xFF0000, w);
	}
	else
	{
		draw_line(w->player.x, w->player.y, (int)hit_vert.x, (int)hit_vert.y, 0xFF0000, w);
	}
}

void		draw_rays(t_win *w)
{
	t_ray	r[w->R_width];
	int		i;
	double	ray_angle;

	// 초기화
	i = 0;
	ray_angle = normalize_angle(w->player.ang + w->fov / 2);
	// printf("r.ang = %f\n", r.ang * 180 / M_PI);
	while (ray_angle > w->player.ang - w->fov / 2)
	{
		r[i].ang = normalize_angle(ray_angle);
		draw_ray(&r[i], w);
		ray_angle -= w->fov / (w->R_width);
		i++;
		printf("카운트 i: %d\n", i);
	}
	mlx_put_image_to_window(w->mlx, w->ptr, w->img.ptr, 0, 0);
	printf("최종 카운트 i: %d\n", i);
}