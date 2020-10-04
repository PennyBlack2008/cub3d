// gcc -I ../minilibx -L ../minilibx -lmlx -framework Appkit -framework OpenGL screen_color.c

/*
** jikang 의 코멘트: 화면에 꽉차게 박스를 그리는 코드. 연습용으로 만들었다.
**
*/


#include <stdio.h>
#include "../minilibx/mlx.h"

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

# define SCREEN_WIDTH WIN_WIDTH
# define SCREEN_HEIGHT WIN_HEIGHT

# define KEY_S			1
# define KEY_D			2
# define KEY_F			3
# define KEY_G			5
# define KEY_H			4
# define KEY_J			38
# define KEY_K			40

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

int					screen_color(t_vars *var)
{
	int		count_w;
	int		count_h;

	count_h = 0;
	while (count_h < SCREEN_HEIGHT)
	{
		count_w = 0;
		while (count_w < SCREEN_WIDTH)
		{
			var->param.img.data[count_h * SCREEN_WIDTH + count_w] = 0x00FF00;
			count_w++;
		}
		count_h++;
	}
	return (0);
}

int	main(void)
{
	t_vars	var;

	// window 설정
	var.mlx = mlx_init();
	var.win = mlx_new_window(var.mlx, WIN_WIDTH, WIN_HEIGHT, "A simple example");

	// image 설정
	var.param.img.ptr = mlx_new_image(var.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	var.param.img.data = (int *)mlx_get_data_addr(var.param.img.ptr, &var.param.img.bpp, &var.param.img.size_l, &var.param.img.endian);

	// screen color 설정
	screen_color(&var);
	mlx_put_image_to_window(var.mlx, var.win, var.param.img.ptr, 0, 0);

	mlx_loop(var.mlx);
	return (0);
}