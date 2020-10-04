#include "cub_28.h"

void					my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char				*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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
	w->player.ang = M_PI_2 * 3;

	// map
	map_init(w);

	return (0);
}

int main(void)
{
	t_win w;

	init_win(&w);

	mlx_loop_hook(w.mlx, render_next_frame, &w);
	mlx_loop(w.mlx);
	return (0);
}