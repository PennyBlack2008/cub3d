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

void		draw_a_wall(int i, t_ray *r, t_win *w)
{
	double dist_to_wall;
	double pjtd_height;

	// printf("%d 번째: r->hit.x is %f, r->hit.y if %f\n", i, r->hit.x, r->hit.y);
	dist_to_wall = hypot(r->hit.x - w->player.x, r->hit.y - w->player.y) * fabs(cos(r->ang - w->player.ang));
	// dist_to_wall = hypot(r->hit.x - w->player.x, r->hit.y - w->player.y);
	// dist_to_wall = hypot(r->x - w->player.x, r->y - w->player.y);
	printf("dist_to_wall : %f\n", dist_to_wall);
	pjtd_height = w->wall.height * w->player.projected_plane / dist_to_wall;
	if (pjtd_height > w->R_height)
		pjtd_height = w->R_height;
	// printf("pjtd_height : %f\n", pjtd_height);
	// printf("w->player.projected_plane : %f\n", w->player.projected_plane);

	int j;		j = 0;		int k;		k = pjtd_height / 2 - 1;

	// 중간인 500 은 위쪽 while 에서 처리
	while (j < pjtd_height / 2)
	{
		my_mlx_pixel_put(&w->img, i, w->player.height + j, 0x00ff00);
		j++;
	}
	while (k > 0)
	{
		my_mlx_pixel_put(&w->img, i, w->player.height - k, 0x00ff00);
		k--;
	}
}
