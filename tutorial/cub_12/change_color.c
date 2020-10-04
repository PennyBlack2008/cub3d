// gcc -I ../minilibx -L ../minilibx -lmlx -framework Appkit -framework OpenGL change_color.c

/*
** jikang 의 코멘트: 박스를 그려서 키를 누를 때마다 해당 키에 관련한 색으로 박스의 색을 바꿔주는 코드
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
# define SCREEN_WIDTH WIN_WIDTH/2
# define SCREEN_HEIGHT WIN_HEIGHT/2

// 키 설정
# define KEY_S			1
# define KEY_D			2
# define KEY_F			3
# define KEY_G			5
# define KEY_H			4


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

int					take_seconds(int sec)
{
	sleep(sec * 1);
	return (0);
}

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

int					screen_color(t_vars *var)
{
	int		count_w;
	int		count_h;

	// mlx_clear_window(var->mlx, var->win);
	count_h = 0;
	while (count_h < SCREEN_HEIGHT)
	{
		count_w = 0;
		while (count_w < SCREEN_WIDTH)
		{
			var->param.img.data[count_h * SCREEN_WIDTH + count_w] = var->param.color;
			count_w++;
		}
		count_h++;
	}
	mlx_put_image_to_window(var->mlx, var->win, var->param.img.ptr, 0, 0);
	return (0);
}

// 시간 당 screen color 바꿔주는 함수
int     render_next_frame(t_vars *var)
{
	mlx_clear_window(var->mlx, var->win);
	screen_color(var);

	return (0);
}

int				key_press(int keycode, t_vars *vars)
{
	vars->param.color = create_trgb(0, 0, 255, 0);

	if (keycode == KEY_S)
		exit(0);
	if (keycode == KEY_D) // clear
		vars->param.color = 0x00bfff; // deep sky blue 색
	if (keycode == KEY_F) // close
		vars->param.color = 0x0000ff; // sky blue 색
	if (keycode == KEY_G)
		vars->param.color = 0x00FF00; // green 색

	return (0);
}


int     main(void)
{
	t_vars	var;

	// window 설정
	var.mlx = mlx_init();
	var.win = mlx_new_window(var.mlx, WIN_WIDTH, WIN_HEIGHT, "A simple example");

	// image 설정
	var.param.img.ptr = mlx_new_image(var.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	var.param.img.data = (int *)mlx_get_data_addr(var.param.img.ptr, &var.param.img.bpp, &var.param.img.size_l, &var.param.img.endian);

	mlx_key_hook(var.win, key_press, &var); // 여기는 키를 누르는 것만 받고
	mlx_loop_hook(var.mlx, render_next_frame, &var);
	mlx_loop(var.mlx);

	return (0);
}