// gcc -I ../../minilibx_opengl_20191021 -L ../../minilibx_opengl_20191021 -lmlx -framework Appkit -framework OpenGL getting_started_square.c
#include "../minilibx/mlx.h"
#include <stdio.h>
#include <stdlib.h>

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
	mov[X] = 0; mov[Y] = 0;
	// 0x99ccff
	// int color = 0x99ccff;
	int color = 0x501d3f;
	int scale = 400;
	while (mov[Y] < scale)
	{
		mov[X] = 0;
		if (mov[Y] % 40 == 0)
			color += 0x101010;
		while (mov[X] < scale)
		{
			// mlx_pixel_put(img.mlx, img.win, pos[X] + mov[X], pos[Y] + mov[Y], color);
			my_mlx_pixel_put(&img, pos[X] + mov[X], pos[Y] + mov[Y], color);
			mov[X]++;
		}
		mov[Y]++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_hook(img.win, 2, 0, mlx_exit, &img);
	mlx_loop(mlx);
}
