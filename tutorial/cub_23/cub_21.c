#include "cub_21.h"

void					my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char				*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int				key_press(int keycode, t_win *w)
{
	if (keycode == KEY_ESC)
	{
		exit(0);
	}
	if (keycode == KEY_A)
	{
		draw_grid(w);
		draw_player(w);
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
	return (0);
}

int main(void)
{
	t_win	w;					init_struct_win(&w);

	mlx_key_hook(w.win, key_press, &w); // 여기는 키를 누르는 것만 받고
	mlx_loop(w.mlx);

	return (0);
}
