#include "cub_21.h"

#define NINETY_DEGREE 90 * M_PI / 180
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
	draw_map(w);
	// ROW, COL 가 뒤섞여서 segfault!!!
	// draw_rectangle(w, 0, 3, 0xff0000);
	// draw_rectangle(w, 0, 6, 0xffccff);
	draw_player(w);
	draw_line(0, 0, WIN_WIDTH, WIN_HEIGHT, 0x00FF00, w);
	return (0);
}

int				key_press(int keycode, t_win *w)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_image(w->mlx, w->img.ptr);
		mlx_destroy_window(w->mlx, w->win);
		exit(1);
	}
	if (keycode == KEY_W) // 플레이어 정면으로 이동
	{
		w->player.x += 10 * cos(w->player.ang * -1);
		w->player.y -= 10 * sin(w->player.ang * -1);
		printf("player 위치 : %d %d\n", w->player.x, w->player.y);
	}
	if (keycode == KEY_A) // 플레이어 왼쪽으로 이동
	{
		w->player.x -= 10 * cos(M_PI_2 - (w->player.ang * -1));
		w->player.y -= 10 * sin(M_PI_2 - (w->player.ang * -1));
	}
	if (keycode == KEY_S) // 플레이어 뒤쪽으로 이동
	{
		w->player.x -= 10 * cos(w->player.ang * -1);
		w->player.y += 10 * sin(w->player.ang * -1);
		printf("player 위치 : %d %d\n", w->player.x, w->player.y);
	}
	if (keycode == KEY_D) // 플레이어 오른쪽으로 이동
	{
		w->player.x += 10 * cos(M_PI_2 - (w->player.ang * -1));
		w->player.y += 10 * sin(M_PI_2 - (w->player.ang * -1));
	}
	if (keycode == KEY_LEFT) // 각도 왼쪽으로
	{
		w->player.ang -= 30 * M_PI / 180;
	}
	if (keycode == KEY_RIGHT) // 각도 오른쪽으로
	{
		w->player.ang += 30 * M_PI / 180;
	}
	if (keycode == KEY_H)
	{
		// draw_line(0, 0, WIN_WIDTH, WIN_HEIGHT, 0x00FF00, w);
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

	// 윈도우
	w->win = mlx_new_window(w->mlx, w->R_width, w->R_height, "veryluckymanjinwoo");

	// 이미지 size: 30 X 30
	w->img.ptr = mlx_new_image(w->mlx, WIN_WIDTH, WIN_HEIGHT);		w->img.addr = mlx_get_data_addr(w->img.ptr, &w->img.bits_per_pixel, &w->img.line_length, &w->img.endian);
	w->img.x = 0;		w->img.y = 0; // 이미지의 위치

	// player
	w->player.x = WIN_WIDTH / 2;
	w->player.y = WIN_HEIGHT / 2;
	w->player.ang = 0 * M_PI / 180;

	// map
	map_init(w);

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
