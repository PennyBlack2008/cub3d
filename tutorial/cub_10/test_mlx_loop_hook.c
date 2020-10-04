// https://harm-smits.github.io/42docs/libs/minilibx/prototypes.html
// gcc -I ../minilibx -L ../minilibx -lmlx -framework Appkit -framework OpenGL test_mlx_loop_hook.c

/*
** int     mlx_loop_hook (void *mlx_ptr, int (*f)(), void *param);
**
** Loop over the given mlx pointer.
** Each hook that was registered prior to this will be called accordingly by order of registration.
*/

/*
** jikang 의 코멘트: mlx_loop_hook 안에 들어있는 함수는 계속 반복적으로 작동된다.
**
*/


#include "../minilibx/mlx.h"
#include <stdlib.h>
#include <stdio.h>

# define KEY_S			1
# define KEY_D			2
# define KEY_F			3
# define KEY_G			5
# define KEY_H			4
# define KEY_J			38
# define KEY_K			40

# define IMG_HEIGHT		100
# define IMG_WIDTH		100

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

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

void			rectangle(t_vars *vars)
{
	int count_h;
	int count_w;

	count_h = 0;
	while (count_h < IMG_HEIGHT) // 여기서 ++을 해주는듯
	{
		count_w = 0;
		while (count_w < IMG_WIDTH)
		{
			// img.data 가 1차원 배열로 되어 있는 것으로 유추했을 때
			// 우리가 창으로 보는 image가 2차원이지만, 사실은 1차원인 픽셀이 늘어져있는 줄인 것같다.
			// 그렇게 하려면
			if (count_w % 2 == 1) // count_w가 홀수이면 하얀색
				vars->param.img.data[count_h * IMG_WIDTH + count_w] = 0xFFFFFF; // img.data의 배열에 픽셀 색 값을 넣어주는 듯,
			else // count_w가 짝수이면 초록색
				vars->param.img.data[count_h * IMG_WIDTH + count_w] = 0x6AA84F;
			// img.data 배열이 어떻게 만들어져있을까? 왜 1차원 배열인데 넓이와 높이를 더해서 픽셀의 색 값이 정해질까?
			// 내가 생각하기에는 이차원 배열이어야 할 것같은데? 이 이유를 알면 곱하기 4를 하거나 (int *)로 캐스팅하는 이유가 밝혀질 것같다.
			// img.data 는 t_img 구조체의 int * 포인터일 뿐인데, img.data를 받는 함수를 이해하는 것이 더 중요할 것같다.
			count_w++;
		}
		count_h++;
	}

}

int				loop_hook(t_vars *vars)
{
	return (0);
}

int				key_press(int keycode, t_vars *vars)
{
	// int keycode = vars->param.key;

	vars->param.color = create_trgb(0, 0, 255, 0);

	if (keycode == KEY_S)
		exit(0);
	if (keycode == KEY_D) // clear
		mlx_clear_window(vars->mlx, vars->win); // 플레이어가 움직일 때마다 함수 실행시켜주면 좋고 이 함수를 안쓰고 픽셀겹쳐도 놓아도 좋고
	if (keycode == KEY_F) // close
		mlx_destroy_window(vars->mlx, vars->win);
	if (keycode == KEY_G)
		mlx_get_color_value(vars->mlx, vars->param.color);
	if (keycode == KEY_H)
	{
		vars->param.str = "cub3d!!";
		mlx_string_put(vars->mlx, vars->win, vars->param.x, vars->param.y, vars->param.color, vars->param.str);
	}
	/*if (keycode == KEY_H)
		mlx_pixel_put(vars->mlx, vars->win, vars->param.x, vars->param.y, vars->param.color);*/
	if (keycode == KEY_J)
	{
		vars->param.str = "cub3d1234567";
		mlx_string_put(vars->mlx, vars->win, vars->param.x, vars->param.y, vars->param.color, vars->param.str);
	}
	if (keycode == KEY_K)
	{
		vars->param.img.ptr = mlx_new_image(vars->mlx, IMG_WIDTH, IMG_HEIGHT);
		vars->param.img.data = (int *)mlx_get_data_addr(vars->param.img.ptr, &vars->param.img.bpp, &vars->param.img.size_l, &vars->param.img.endian);
		rectangle(vars);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->param.img.ptr, 400 - (IMG_WIDTH / 2), 240 - (IMG_HEIGHT / 2)); // 이미지 포인터를 파라미터로 넣어 그 이미지 위치를 정해준다.
	}
	return (0);
}

int					main(void)
{
	t_vars			vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 800, 480, "test");
	vars.param.x = 400;
	vars.param.y = 240;
	mlx_key_hook(vars.win, key_press, &vars); // 여기는 키를 누르는 것만 받고
	mlx_loop_hook(vars.mlx, loop_hook, &vars);
	mlx_loop(vars.mlx);
}