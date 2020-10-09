#include "cub_21.h"

void		draw_wall(int i, t_ray *r, t_win *w)
{
	double dist;
	double pjtd_height;

	printf("%d 번째: r->x is %f, r->y if %f\n", i, r->x, r->y);
	dist = hypot(r->x - w->player.x, r->y - w->player.y) * cos(r->ang);
	// printf("dist : %f\n", dist);
	pjtd_height = w->wall.height * dist / w->player.projected_plane;
	if (pjtd_height > 999)
		pjtd_height = 999;
	// printf("pjtd_height : %f\n", pjtd_height);
	// printf("w->player.projected_plane : %f\n", w->player.projected_plane);

	int j;		j = 0;		int k;		k = pjtd_height / 2 - 1;

	// 중간인 500 은 위쪽 while 에서 처리
	while (j < pjtd_height / 2)
	{
		my_mlx_pixel_put(&w->img, i, 500 + j, 0x00ff00);
		j++;
	}
	while (k > 0)
	{
		my_mlx_pixel_put(&w->img, i, 500 - k, 0x00ff00);
		k--;
	}
}
