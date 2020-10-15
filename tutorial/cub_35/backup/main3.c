#include <stdio.h>
#include "../minilibx/mlx.h"
#include "../libft/libft.h"
#include <math.h>

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

int					round_num(double num)
{
	if (num >= 0.5)
		num = (int)num + 1;
	else
		num = (int)num;

	return (num);
}

int					main()
{
	t_win			win;
	int				h;
	int				w;
	int				i, j, k;
	double			px, py;
	double			scale_w;
	double			scale_h;

	// window 설정
	win.mlx = mlx_init();
	win.ptr = mlx_new_window(win.mlx, 500, 500, "veryluckymanjinwoo");

	// 첫 번째 이미지(화면 전체 담당)
	win.img.ptr = mlx_new_image(win.mlx, 500, 500);
	win.img.addr = mlx_get_data_addr(win.img.ptr, &win.img.bpp, &win.img.len, &win.img.endian);

	// 두 번째 이미지(텍스쳐 이미지 받아오는 것 담당): 이미지 값을 win.curr_tex에 저장하고 win.tex.ptr 은 폐기
	win.tex.ptr = mlx_xpm_file_to_image(win.mlx, "eagle.xpm", &win.tex.width, &win.tex.height);
	win.tex.addr = (int *)mlx_get_data_addr(win.tex.ptr, &win.tex.bpp, &win.tex.len, &win.tex.endian);

	win.curr_tex = (int *)ft_calloc((win.tex.height * win.tex.width), sizeof(int));
	i = 0;
	while (i < win.tex.height)
	{
		j = 0;
		while (j < win.tex.width)
		{
			win.curr_tex[(int)win.tex.width * i + j] = win.tex.addr[(int)win.tex.width * i + j];
			j++;
		}
		i++;
	}
	mlx_destroy_image(win.mlx, win.tex.ptr);

	// 두 번째 이미지를 윈도우에 출력해보기
	scale_w = 2;
	scale_h = 4;
	i = 0;
	while (i < 64 * scale_w) // width
	{
		j = 0;
		while (j < 64 * scale_h) // height
		{
			px = floor(i / scale_w);
			py = floor(j / scale_h);
			my_mlx_pixel_put(&win.img, i, j, win.curr_tex[(int)(64 * py + px)]);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(win.mlx, win.ptr, win.img.ptr, 0, 0);
	mlx_loop(win.mlx);

	return (0);
}
