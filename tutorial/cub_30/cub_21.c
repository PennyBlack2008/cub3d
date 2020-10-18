#include "cub_21.h"

void					my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char				*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int     render_next_frame(t_win *w)
{
	draw_background(w);
	// draw_grid(w);
	// draw_line(0, 0, WIN_WIDTH, WIN_HEIGHT, 0x00FF00, w);
	cast_rays(w);
	// draw_map(w);
	// draw_player(w);
	return (0);
}

int				key_press(int keycode, t_win *w)
{
	int			pixel_x, pixel_y;
	double		a, b, c, h;
	double		angle;

	if (keycode == KEY_ESC)
	{
		mlx_destroy_image(w->mlx, w->img.ptr);
		mlx_destroy_window(w->mlx, w->win);
		exit(1);
	}
	if (keycode == KEY_W) // 위로
	{
		// w->player.y -= 10;
		if (move_forward(w) == WALL)
			printf("벽을 뚫고 지나가지 못합니다.\n");
	}
	if (keycode == KEY_A) // 왼쪽으로
	{
		// w->player.x -= 10;
		if (move_left(w) == WALL)
			printf("벽을 뚫고 지나가지 못합니다.\n");
	}
	if (keycode == KEY_S) // 밑으로
	{
		// w->player.y += 10;
		if (move_back(w) == WALL)
			printf("벽을 뚫고 지나가지 못합니다.\n");
	}
	if (keycode == KEY_D) // 오른쪽으로
	{
		// w->player.x += 10;
		if (move_right(w) == WALL)
			printf("벽을 뚫고 지나가지 못합니다.\n");
	}
	if (keycode == KEY_LEFT) // 각도 왼쪽으로
	{
		if (rotate_left(w) == WALL)
			printf("벽을 뚫고 회전하지 못합니다.\n");
	}
	if (keycode == KEY_RIGHT) // 각도 오른쪽으로
	{
		if (rotate_right(w) == WALL)
			printf("벽을 뚫고 회전하지 못합니다.\n");
	}
	if (keycode == KEY_H)
	{
		draw_line(0, 0, WIN_WIDTH, WIN_HEIGHT, 0x00FF00, w);
		draw_line(0, 0, WIN_WIDTH, WIN_HEIGHT, 0x00FF00, w);
		draw_line(0, 0, WIN_WIDTH, WIN_HEIGHT, 0x00FF00, w);
		draw_line(0, 0, WIN_WIDTH, WIN_HEIGHT, 0x00FF00, w);

	}
	if (keycode == KEY_G)
	{
		mlx_clear_window(w->mlx, w->win);
	}

	return (0);
}

int					init_struct_win(t_win *w)
{
	// mlx init
	w->mlx = mlx_init();

	// 해상도
	w->R_width = WIN_WIDTH;
	w->R_height = WIN_HEIGHT;
	w->player.projected_plane = w->R_width / 2 * atan(M_PI_2 / 3);

	// 윈도우
	w->win = mlx_new_window(w->mlx, w->R_width, w->R_height, "veryluckymanjinwoo");

	// 이미지 size: 30 X 30
	w->img.ptr = mlx_new_image(w->mlx, WIN_WIDTH, WIN_HEIGHT);		w->img.addr = mlx_get_data_addr(w->img.ptr, &w->img.bits_per_pixel, &w->img.line_length, &w->img.endian);
	w->img.x = 0;		w->img.y = 0; // 이미지의 위치

	// wall
	w->wall.length = 100;
	w->wall.height = 600;

	// player
	w->player.width = w->wall.length / 3;
	w->player.height = w->wall.length / 3;
	w->player.x = 4 * w->wall.length;
	w->player.y = 4 * w->wall.length;
	w->player.ang = 0 * M_PI / 180;

	// map
	map_init(w);

	// minimap
	w->mini.plot.x = w->R_width - 300;
	w->mini.plot.y = w->R_height - 300;

	return (0);
}

int main(void)
{
	t_win	w;					init_struct_win(&w);

	mlx_key_hook(w.win, key_press, &w); // 여기는 키를 누르는 것만 받고
	mlx_loop_hook(w.mlx, render_next_frame, &w);
	mlx_loop(w.mlx);

	return (0);
}
