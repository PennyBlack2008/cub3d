// https://harm-smits.github.io/42docs/libs/minilibx/prototypes.html
// gcc -I ../minilibx -L ../minilibx -lmlx -framework Appkit -framework OpenGL test_mlx_new_image.c

/*
** void    *mlx_new_image(void *mlx_ptr,int width,int height);
**
** Creates a new MLX compatible image.
** This is the recommended way to buffer the image you are rendering to be displayed.
** It will accept a pointer to your mlx instance and requires a width and height.
** Will return a reference pointer to the image.
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
	while (count_h < IMG_HEIGHT)
	{
		count_w = 0;
		while (count_w < IMG_WIDTH)
		{
			if (count_w % 2 == 1)
				vars->param.img.data[count_h * IMG_WIDTH + count_w] = 0xFFFFFF;
			else
				vars->param.img.data[count_h * IMG_WIDTH + count_w] = 0x6AA84F;
			count_w++;
		}
		count_h++;
	}

}
int				key_press(int keycode, t_vars *vars)
{
	// int keycode = vars->param.key;

	vars->param.color = create_trgb(0, 0, 255, 0);

	if (keycode == KEY_S)
		exit(0);
	if (keycode == KEY_D) // clear
		mlx_clear_window(vars->mlx, vars->win);
	if (keycode == KEY_F) // close
		mlx_destroy_window(vars->mlx, vars->win);
	if (keycode == KEY_G)
		mlx_get_color_value(vars->mlx, vars->param.color);
	if (keycode == KEY_H)
		mlx_pixel_put(vars->mlx, vars->win, vars->param.x, vars->param.y, vars->param.color);
	if (keycode == KEY_J)
	{
		vars->param.str = "cub3d";
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
	mlx_loop(vars.mlx);
}