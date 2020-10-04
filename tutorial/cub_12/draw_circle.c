// gcc -I ../minilibx -L ../minilibx -lmlx -framework Appkit -framework OpenGL draw_circle.c

// 이 코드의 결과는 윈도우(넓이 800, 높이 600)의 까만 창에 이미지(넓이 800, 높이 600)가 들어간다.
// 이 이미지를 main문의 while문을 통해 색을 입히는 것이다.

/*
** jikang 의 코멘트: 초록색 원을 그리는 코드, 그 이상 그 이하도 아닌......
**
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../minilibx/mlx.h"

// 윈도우 해상도 설정
# define WIN_WIDTH 800
# define WIN_HEIGHT 600

// 이미지 해상도 설정
# define CIRCLE_WIDTH 200
# define CIRCLE_HEIGHT 200

typedef struct	s_img
{
	void		*ptr; // 이미지 포인터
	char		*addr;
	int			line_length;
	int			bpp;
	int			endian;
}				t_img;

typedef struct	s_param
{
	int			key;
	int			x;
	int			y;
	int			color;
	char		*str;
	t_img		img;
}				t_param;

typedef struct		s_vars
{
	void			*mlx;
	void			*win;
	t_param			param;
}					t_vars;

void					my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char				*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

int		cal_square(int num)
{
	return (num * num);
}

int					draw_circle(t_vars *var)
{
	int		count_w;
	int		count_h;
	int		R;

	R = 100;
	count_h = 0;
	while (count_h < 2 * R)
	{
		count_w = 0;
		while (count_w < 2 * R)
		{
			if ((cal_square(count_w - R) + cal_square(count_h - R)) <= (R * R))
			{
				my_mlx_pixel_put(&var->param.img, count_w, count_h, var->param.color);
			}
			count_w++;
		}
		count_h++;
	}
	mlx_put_image_to_window(var->mlx, var->win, var->param.img.ptr, 0, 0);

	return (0);
}


int     main(void)
{
	t_vars	var;

	// window 설정
	var.mlx = mlx_init();
	var.win = mlx_new_window(var.mlx, WIN_WIDTH, WIN_HEIGHT, "A simple example");

	// image 설정
	var.param.img.ptr = mlx_new_image(var.mlx, CIRCLE_WIDTH, CIRCLE_HEIGHT);
	var.param.img.addr = (char *)mlx_get_data_addr(var.param.img.ptr, &var.param.img.bpp, &var.param.img.line_length, &var.param.img.endian);

	// screen 설정(이미지)
	var.param.color = 0x00FF00;
	draw_circle(&var);

	mlx_loop(var.mlx);

	return (0);
}