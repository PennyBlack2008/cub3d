#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../libft/libft.h"
#include "../minilibx/mlx.h"

# define ABS(N) ((N < 0) ? (-N) : (N))

typedef struct	s_coord
{
	int			x;
	int			y;
} 				t_coord;

typedef struct	s_img
{
	void        *ptr;
	char        *addr; // 이 변수에 image 픽셀의 색을 넣어주는 것이 이미지를 만드는 것이다.
	int         bits_per_pixel;
	int         line_length;
	int         endian;
}				t_img;

typedef struct	s_win
{
	void *mlx;
	void *win;
	t_img img;
}				t_win;

void					my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char				*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
	// printf("%d, %d\n", x, y);
}

int						mark_pixel(t_coord *p, t_win *w)
{
	my_mlx_pixel_put(&w->img, p->x, p->y, 0x00FF00);
	return (0);
}

static void plot_line_low(t_coord *p1, t_coord *p2, t_win *w)
{
	int			dx;
	int			dy;
	int			yi;
	int			D;
	t_coord		p;

	p = *p1;
	dx = p2->x - p1->x;
	dy = p2->y - p1->y;
	yi = 1;
	if (dy < 0 && (yi = -1))
		dy = -dy;
	D = 2 * dy - dx;
	while (p.x <= p2->x)
	{
		mark_pixel(&p, w);
		if (D > 0)
		{
			p.y += yi;
			D -= 2 * dx;
		}
		D += 2 * dy;
		p.x++;
	}
}

static void plot_line_high(t_coord *p1, t_coord *p2, t_win *w)
{
	int			dx;
	int			dy;
	int			xi;
	int			D;
	t_coord	p;

	p = *p1;
	dx = p2->x - p1->x;
	dy = p2->y - p1->y;
	xi = 1;
	if (dx < 0 && (xi = -1))
		dx = -dx;
	D = 2 * dx - dy;
	while (p.y <= p2->y)
	{
		mark_pixel(&p, w);
		if (D > 0)
		{
			p.x += xi;
			D -= 2 * dy;
		}
		D += 2 * dx;
		p.y++;
	}
}

void plot_line(t_coord *p1, t_coord *p2, t_win *w)
{
	if (ABS(p2->x - p1->x) > ABS(p2->y - p1->y))
	{
		if (p2->x > p1->x)
			plot_line_low(p1, p2, w);
		else
			plot_line_low(p2, p1, w);
	}
	else
	{
		if (p2->y > p1->y)
			plot_line_high(p1, p2, w);
		else
			plot_line_high(p2, p1, w);
	}
}

void	initialize_win(t_win *w)
{
	w->mlx = mlx_init();
	w->win = mlx_new_window(w->mlx, 700, 700, "veryluckymanjinwoo");
	w->img.ptr = mlx_new_image(w->mlx, 700, 700);
	w->img.addr = (char *)mlx_get_data_addr(w->img.ptr, &w->img.bits_per_pixel, &w->img.line_length, &w->img.endian);
}

int main(void)
{
	t_win	w;		initialize_win(&w);

	t_coord p1;
	p1.x = 0;	p1.y = 0;

	t_coord p2;
	p2.x = 700;	p2.y = 300;

	plot_line(&p1, &p2, &w);
	mlx_put_image_to_window(w.mlx, w.win, w.img.ptr, 0, 0);
	mlx_loop(w.mlx);
}