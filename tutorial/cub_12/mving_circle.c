// gcc -I ../minilibx -L ../minilibx -lmlx -framework Appkit -framework OpenGL mving_circle.c

/*
** jikang 의 코멘트: 원을 키를 눌러서 움직여보는 코드
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

// 키 설정
# define KEY_S			1
# define KEY_D			2
# define KEY_F			3
# define KEY_G			5
# define KEY_H			4
# define KEY_W			13
# define KEY_A			0


typedef struct	s_img
{
	void		*ptr; // 이미지 포인터
	int			*data;
	int			size_l;
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

int		cal_square(int num)
{
	return (num * num);
}

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

int					draw_circle(t_vars *var)
{
	int		count_w;
	int		count_h;
	int		R;

	R = 100;
	count_h = 0;
	while (count_h < CIRCLE_HEIGHT)
	{
		count_w = 0;
		while (count_w < CIRCLE_WIDTH)
		{
			if ((cal_square(count_w - CIRCLE_WIDTH/2) + cal_square(count_h - CIRCLE_HEIGHT/2)) <= (R * R))
			{
				var->param.img.data[count_h * CIRCLE_WIDTH + count_w] = var->param.color;
			}
			count_w++;
		}
		count_h++;
	}
	mlx_put_image_to_window(var->mlx, var->win, var->param.img.ptr, var->param.x, var->param.y);

	return (0);
}

// 시간 당 screen color 바꿔주는 함수
int     render_next_frame(t_vars *var)
{
	mlx_clear_window(var->mlx, var->win);
	draw_circle(var);

	return (0);
}

int				key_press(int keycode, t_vars *var)
{
	if (keycode == KEY_W)
		var->param.y -= 10;
	if (keycode == KEY_A)
		var->param.x -= 10;
	if (keycode == KEY_S)
		var->param.y += 10;
	if (keycode == KEY_D)
		var->param.x += 10;
	if (keycode == KEY_F)
		var->param.color = 0x0000ff; // sky blue 색

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
	var.param.img.data = (int *)mlx_get_data_addr(var.param.img.ptr, &var.param.img.bpp, &var.param.img.size_l, &var.param.img.endian);
	var.param.color = create_trgb(0, 0, 255, 0);

	// x, y 좌표 초기화
	var.param.x = 0;
	var.param.y = 0;

	// mlx_put_image_to_window(var.mlx, var.win, var.param.img.ptr, 0, 0);
	mlx_key_hook(var.win, key_press, &var); // 여기는 키를 누르는 것만 받고
	mlx_loop_hook(var.mlx, render_next_frame, &var);
	mlx_loop(var.mlx);

	return (0);
}