#include "cub_21.h"

/*
**	bresenhem algorithm
*/
static void plot_line_low(int p1_x, int p1_y, int p2_x, int p2_y, int color, t_win *w)
{
	int			dx;
	int			dy;
	int			yi;
	int			D;
	// t_coord		p;
	int			p_x;
	int			p_y;

	p_x = p1_x;
	p_y = p1_y;
	dx = p2_x - p1_x;
	dy = p2_y - p1_y;
	yi = 1;
	if (dy < 0 && (yi = -1))
		dy = -dy;
	D = 2 * dy - dx;
	while (p_x <= p2_x)
	{
		my_mlx_pixel_put(&w->img, p_x, p_y, color);
		// mark_pixel(&p_x, &p_y, w);
		if (D > 0)
		{
			p_y += yi;
			D -= 2 * dx;
		}
		D += 2 * dy;
		p_x++;
	}
}

static void plot_line_high(int p1_x, int p1_y, int p2_x, int p2_y, int color, t_win *w)
{
	int			dx;
	int			dy;
	int			xi;
	int			D;
	// t_coord	p;
	int			p_x;
	int			p_y;

	p_x = p1_x;
	p_y = p1_y;
	dx = p2_x - p1_x;
	dy = p2_y - p1_y;
	xi = 1;
	if (dx < 0 && (xi = -1))
		dx = -dx;
	D = 2 * dx - dy;
	while (p_y <= p2_y)
	{
		my_mlx_pixel_put(&w->img, p_x, p_y, color);
		// mark_pixel(&p_x, &p_y, w);
		if (D > 0)
		{
			p_x += xi;
			D -= 2 * dy;
		}
		D += 2 * dx;
		p_y++;
	}
}

void draw_line(int p1_x, int p1_y, int p2_x, int p2_y, int color, t_win *w)
{
	if (abs(p2_x - p1_x) > abs(p2_y - p1_y)) // 기울기 45도 이하일 경우
	{
		if (p2_x > p1_x)
			plot_line_low(p1_x, p1_y, p2_x, p2_y, color, w);
		else
			plot_line_low(p2_x, p2_y, p1_x, p1_y, color, w);
	}
	else // 기울기 45도 이상일 경우
	{
		if (p2_y > p1_y)
			plot_line_high(p1_x, p1_y, p2_x, p2_y, color, w);
		else
			plot_line_high(p2_x, p2_y, p1_x, p1_y, color, w);
	}
	// mlx_put_image_to_window(w->mlx, w->win, w->img.ptr, 0, 0);
}