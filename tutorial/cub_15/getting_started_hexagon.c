// gcc -I ../../minilibx_opengl_20191021 -L ../../minilibx_opengl_20191021 -lmlx -framework Appkit -framework OpenGL getting_started_hexagon.c

#include "/Users/veryluckymanjinwoo/Documents/Pennymannibanni/42cursus/cub3D/minilibx_opengl_20191021/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

# define X 0
# define Y 1

typedef struct  s_data {
	void		*mlx;
	void		*win;
	void		*img;

	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
	return ;
}

int mlx_exit(int keycode, void *param)
{
	t_data *img = param;
	if(keycode == 53)
	{
		printf("esc\n");
		mlx_destroy_window(img->mlx, img->win);
		exit(0);
	}
	return (1);
}


int	main(void)
{
    void    *mlx;
    void    *mlx_win;
	int start;
	int end;
    t_data  img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1000, 1000, "Hello world!");
	img.win = mlx_win;
	img.mlx = mlx;
	img.img = mlx_new_image(mlx, 1000, 1000);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
									&img.endian);

	double pos[2];
	pos[X] = 500; pos[Y] = 500;
	double dir[2];
	dir[X] = 1; dir[Y] = 0;
	double dir_temp;
	int i = 0;
	int count = 6;
	double scale = 200;
	int color = 0x99ccff; // sky blue

	while (scale > 0)
	{
		count = 6;
		while (count > 0)
		{
			i = 0;
			// color -= 0x100010;
			while (i < scale)
			{
				pos[X] += dir[X];
				pos[Y] += dir[Y];
				my_mlx_pixel_put(&img, pos[X], pos[Y], color);
				i++;
			}
			dir_temp = dir[X];
			dir[X] = cos(M_PI/3) * dir[X] - sin(M_PI/3) * dir[Y];
			dir[Y] = sin(M_PI/3) * dir_temp + cos(M_PI/3) * dir[Y];
			printf("dir[X] dir[Y] : %f %f\n", dir[X], dir[Y]);
			count--;
		}
		scale -= 0.02;
	}

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_hook(img.win, 2, 0, mlx_exit, &img);
	mlx_loop(mlx);
}
