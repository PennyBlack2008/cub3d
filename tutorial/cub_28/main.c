#include "cub_28.h"

void					my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char				*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int				key_press(int keycode, t_win *w)
{
	int			pixel_x, pixel_y;
	double		a, b, c, h;
	double		angle;

	if (keycode == KEY_ESC)
	{
		mlx_destroy_image(w->mlx, w->img.ptr);
		mlx_destroy_window(w->mlx, w->ptr);
		exit(1);
	}
	if (keycode == KEY_W) // 위로
	{
		if (move_forward(w) == WALL)
			printf("벽을 뚫고 지나가지 못합니다.\n");
	}
	if (keycode == KEY_A) // 왼쪽으로
	{
		if (move_left(w) == WALL)
			printf("벽을 뚫고 지나가지 못합니다.\n");
	}
	if (keycode == KEY_S) // 밑으로
	{
		if (move_back(w) == WALL)
			printf("벽을 뚫고 지나가지 못합니다.\n");
	}
	if (keycode == KEY_D) // 오른쪽으로
	{
		if (move_right(w) == WALL)
			printf("벽을 뚫고 지나가지 못합니다.\n");
	}
	if (keycode == KEY_LEFT) // 각도 왼쪽으로
	{
		if (rotate_left(w) == WALL)
			printf("벽을 뚫고 회전하지 못합니다.\n");
		normalize_angle(w->player.ang);
	}
	if (keycode == KEY_RIGHT) // 각도 오른쪽으로
	{
		if (rotate_right(w) == WALL)
			printf("벽을 뚫고 회전하지 못합니다.\n");
		normalize_angle(w->player.ang);
	}
	if (keycode == KEY_H)
	{
		// draw_line(0, 0, WIN_WIDTH, WIN_HEIGHT, 0x00FF00, w);
	}
	if (keycode == KEY_G)
	{
		mlx_clear_window(w->mlx, w->ptr);
	}

	return (0);
}


int	render_next_frame(t_win *w)
{
	draw_map(w);
	draw_rays(w);
	draw_line(0, 0, w->R_width, w->R_height, 0x00FF00, w);

	return (0);
}

int	init_win(t_win *w)
{
	w->mlx = mlx_init();

	// win
	w->R_width = 1000;
	w->R_height = 1000;
	w->ptr = mlx_new_window(w->mlx, w->R_width, w->R_height, "veryluckymanjinwoo");
	w->fov = M_PI / 3;

	// img
	w->img.ptr = mlx_new_image(w->mlx, w->R_width, w->R_height);
	w->img.addr = mlx_get_data_addr(w->img.ptr, &w->img.bits_per_pixel, &w->img.line_length, &w->img.endian);

	// player
	w->player.x = 500;
	w->player.y = 500;
	w->player.ang = 0 / 180;

	// map
	map_init(w);

	return (0);
}

int main(void)
{
	t_win w;

	init_win(&w);

	mlx_key_hook(w.ptr, key_press, &w); // 여기는 키를 누르는 것만 받고
	mlx_loop_hook(w.mlx, render_next_frame, &w);
	mlx_loop(w.mlx);
	return (0);
}
