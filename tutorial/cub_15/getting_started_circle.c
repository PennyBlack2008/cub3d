// gcc -I ../../minilibx_opengl_20191021 -L ../../minilibx_opengl_20191021 -lmlx -framework Appkit -framework OpenGL getting_started_circle.c

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
	int pos[2];
	int mov[2];
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

	pos[X] = 500; pos[Y] = 500;
	mov[X] = 100; mov[Y] = 100;
	int temp_x;
	int temp_y;
	int rad = 0;
	int scale = 500;
	int color = 0x99ccff; // skyblue
	while (mov[X] > 0)
	{
		if (mov[X] % 10 == 0)
			color += 0x051010;
		rad = 0;
		while (rad < scale)
		{
			temp_x = cos(rad) * mov[X] - sin(rad) * mov[Y];
			temp_y = sin(rad) * mov[X] + cos(rad) * mov[Y];
			my_mlx_pixel_put(&img, pos[X] + temp_x, pos[Y] + temp_y, color);
			rad++;
		}
		mov[X]--;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_hook(img.win, 2, 0, mlx_exit, &img);
	mlx_loop(mlx);
}
