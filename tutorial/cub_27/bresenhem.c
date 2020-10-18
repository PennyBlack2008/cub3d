#include "cub_21.h"

/*
**	bresenhem algorithm
*/
static void plot_line_low(t_plot p1, t_plot p2, int color, t_win *w)
{
	int			dx;
	int			dy;
	int			yi;
	int			D;
	t_plot		p;

	p.x = p1.x;
	p.y = p1.y;
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	yi = 1;
	if (dy < 0 && (yi = -1))
		dy = -dy;
	D = 2 * dy - dx;
	while (p.x <= p2.x)
	{
		my_mlx_pixel_put(&w->img, p.x, p.y, color);
		if (D > 0)
		{
			p.y += yi;
			D -= 2 * dx;
		}
		D += 2 * dy;
		p.x++;
	}
}

static void plot_line_high(t_plot p1, t_plot p2, int color, t_win *w)
{
	int			dx;
	int			dy;
	int			xi;
	int			D;
	t_plot		p;

	p.x = p1.x;
	p.y = p1.y;
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	xi = 1;
	if (dx < 0 && (xi = -1))
		dx = -dx;
	D = 2 * dx - dy;
	while (p.y <= p2.y)
	{
		my_mlx_pixel_put(&w->img, p.x, p.y, color);
		if (D > 0)
		{
			p.x += xi;
			D -= 2 * dy;
		}
		D += 2 * dx;
		p.y++;
	}
}

void draw_line(t_plot p1, t_plot p2, int color, t_win *w)
{
	if (fabs(p2.x - p1.x) > fabs(p2.y - p1.y)) // 기울기 45도 이하일 경우
	{
		if (p2.x > p1.x)
			plot_line_low(p1, p2, color, w);
		else
			plot_line_low(p2, p1, color, w);
	}
	else // 기울기 45도 이상일 경우
	{
		if (p2.y > p1.y)
			plot_line_high(p1, p2, color, w);
		else
			plot_line_high(p2, p1, color, w);
	}
}