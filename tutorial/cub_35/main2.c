#include <stdio.h>
#include "../minilibx/mlx.h"
#include "../libft/libft.h"

typedef struct		s_img
{
	void			*ptr;
	int				*addr;
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
	int				x;
	int				y;
}					t_tex;

typedef struct		s_win
{
	void			*mlx;
	void			*ptr;
	t_img			img;
	t_tex			tex;
	int				*curr_tex;
}					t_win;

void					my_mlx_pixel_put(t_tex *img, int x, int y, int color)
{
	int					*dst;

	dst = img->addr + (y * img->len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

int					main()
{
	t_win			win;
	int				h;
	int				w;
	int				i, j, k;
	int				x, y;
	char			*cpy;

	win.mlx = mlx_init();
	win.ptr = mlx_new_window(win.mlx, 500, 500, "veryluckymanjinwoo");

	// 첫 번째 이미지(날 것)
	win.img.ptr = mlx_xpm_file_to_image(win.mlx, "eagle.xpm", &win.img.width, &win.img.height);
	win.img.addr = (int *)mlx_get_data_addr(win.img.ptr, &win.img.bpp, &win.img.len, &win.img.endian);//int* 로 해야 xpm 제대로 받아오는 듯... char *는 문자 표현 크기가 작아서..

	// 두 번째 이미지(가공할 것)
	win.tex.ptr = mlx_new_image(win.mlx, win.img.width, win.img.height * 2);
	win.tex.addr = (int *)mlx_get_data_addr(win.tex.ptr, &win.tex.bpp, &win.tex.x, &win.tex.y);

	i = 0;
	while (i < win.img.width) // i 가 height
	{
		j = 0;		k = 0;
		while (j < win.img.height)
		{
			k = j * 2;
			win.tex.addr[k * win.img.width + i] = win.img.addr[j * win.img.width + i];
			win.tex.addr[(k + 1) * win.img.width + i] = win.img.addr[j * win.img.width + i];
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(win.mlx, win.ptr, win.tex.ptr, 0, 0);
	mlx_loop(win.mlx);

	return (0);
}
