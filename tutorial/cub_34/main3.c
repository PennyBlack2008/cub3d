/*
** main3.c
** 여기서 (char *)mlx_get_data_addr(win.tex.ptr, &win.tex.bpp, &win.tex.len, &win.tex.endian); 를 사용할 때
** int * 로 바꾸지 않는다면, xpm 이미지 색이 이상하게 나오는 것을 알 수 있다.
** 그래서 이것을 확인해보는 코드입니다.
*/

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
	char			*addr;
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
	char			*curr_tex;
}					t_win;

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
	win.img.addr = (char *)mlx_get_data_addr(win.img.ptr, &win.img.bpp, &win.img.len, &win.img.endian);//int* 로 해야 xpm 제대로 받아오는 듯... char *는 문자 표현 크기가 작아서..

	// 두 번째 이미지(가공할 것)
	win.tex.ptr = mlx_xpm_file_to_image(win.mlx, "eagle.xpm", &win.tex.x, &win.tex.y);
	win.tex.addr = (char *)mlx_get_data_addr(win.tex.ptr, &win.tex.bpp, &win.tex.len, &win.tex.endian);
	win.curr_tex = (char *)ft_calloc(win.tex.y * win.tex.x, sizeof(char)); // 일자로 동적할당 addr 와 동일한 역할인듯

	y = 0;
	while (y < win.tex.y)
	{
		x = 0;
		while (x < win.tex.x)
		{
			win.curr_tex[(int)win.tex.x * y + x] = win.tex.addr[win.tex.x * y + x];
			x++;
		}
		y++;
	}

	y = 0;
	while (y < win.tex.y)
	{
		x = 0;
		while (x < win.tex.x)
		{
			my_mlx_pixel_put(&win.tex, x, y, win.curr_tex[(int)win.tex.x * y + x]);
			x++;
		}
		y++;
	}

	// mlx_destroy_image(win.mlx, win.tex.ptr);

	mlx_put_image_to_window(win.mlx, win.ptr, win.img.ptr, 250, 250);
	mlx_put_image_to_window(win.mlx, win.ptr, win.tex.ptr, 0, 0);
	mlx_loop(win.mlx);

	return (0);
}
