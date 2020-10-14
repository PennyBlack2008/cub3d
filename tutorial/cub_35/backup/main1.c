#include <stdio.h>
#include "../minilibx/mlx.h"
#include "../libft/libft.h"

typedef struct		s_img
{
	void			*ptr;
	char			*addr;
	int				bpp;
	int				len;
	int				endian;

	// for xpm image
	int				width;
	int				height;
}					t_img;

typedef struct		s_tex
{
	void			*ptr;
	int				*addr;
	int				bpp;
	int				len;
	int				endian;

	// xpm image size
	int				width;
	int				height;
}					t_tex;

typedef struct		s_win
{
	void			*mlx;
	void			*ptr;
	t_img			img;
	t_tex			tex;
	int				*curr_tex;
}					t_win;

void					my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char				*dst;

	dst = img->addr + (y * img->len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
	printf("%d\n", color);
}

int					main()
{
	t_win			win;
	int				h;
	int				w;
	int				i, j, k;
	int				x, y;
	char			*cpy;
	double			scale_w;
	double			scale_h;

	win.mlx = mlx_init();
	win.ptr = mlx_new_window(win.mlx, 500, 500, "veryluckymanjinwoo");

	// 첫 번째 이미지(날 것)
	win.tex.ptr = mlx_xpm_file_to_image(win.mlx, "eagle.xpm", &win.tex.width, &win.tex.height);
	win.tex.addr = (int *)mlx_get_data_addr(win.tex.ptr, &win.tex.bpp, &win.tex.len, &win.tex.endian); //int* 로 해야 xpm 제대로 받아오는 듯... char *는 문자 표현 크기가 작아서..
	printf("tex: %d %d\n", win.tex.width, win.tex.height);

	// 두 번째 이미지(가공할 것)
	win.img.ptr = mlx_new_image(win.mlx, 500, 500);
	win.img.addr = mlx_get_data_addr(win.img.ptr, &win.img.bpp, &win.img.len, &win.img.endian); //int* 로 해야 xpm 제대로 받아오는 듯... char *는 문자 표현 크기가 작아서..
	scale_w = (double)win.tex.width / 300;
	scale_h = (double)win.tex.height / 300;
	printf("scale: %f, %f\n", scale_w, scale_h);
	// i = 0;
	// while (i < 300)
	// {
	// 	j = 0;
	// 	while (j < 300)
	// 	{
	// 		// my_mlx_pixel_put(&win.img, j, i, win.tex.addr[(int)(j * scale_h * win.tex.width + i * scale_w)]);
	// 		printf("%d\n", (int)(j * scale_h * win.tex.width + i * scale_w));
	// 		// my_mlx_pixel_put(&win.img, j, i, 0x0000ff);
	// 		// win.img.ptr = win.img.addr + (y * win.img.len + x * (win.img.bpp / 8));
	// 		j++;
	// 	}
	// 	i++;
	// }

	i = 0;
	while (i < 64)
	{
		j = 0;
		while (j < 64)
		{
			my_mlx_pixel_put(&win.img, j, i, win.tex.addr[i * 64 + j]);
			// my_mlx_pixel_put(&win.img, j, i, 0x0000ff);
			// printf("%d\n", win.tex.addr[i * 64 + j]);
			j++;
		}
		i++;
	}

	mlx_put_image_to_window(win.mlx, win.ptr, win.img.ptr, 0, 0);
	mlx_loop(win.mlx);

	return (0);
}
