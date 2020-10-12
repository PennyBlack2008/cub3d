#include <stdio.h>
#include "../minilibx/mlx.h"
#include "../libft/libft.h"

typedef struct		s_tex
{
	char			*addr;
}					t_tex;


typedef struct		s_img
{
	void			*ptr;
	char			*addr;
	int				bpp;
	int				len;
	int				endian;

	// for xpm image
	int			width;
	int			height;
}					t_img;

typedef struct		s_win
{
	void			*mlx;
	void			*ptr;
	t_img			img;
	t_tex			tex;
}					t_win;

void					my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char				*dst;

	dst = img->addr + (y * img->len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

int					main()
{
	t_win			win;
	int				h;
	int				w;
	int				i, j;

	win.mlx = mlx_init();
	win.ptr = mlx_new_window(win.mlx, 500, 500, "veryluckymanjinwoo");
	win.img.ptr = mlx_xpm_file_to_image(win.mlx, "eagle.xpm", &win.img.width, &win.img.height);
	win.img.addr = mlx_get_data_addr(win.img.ptr, &win.img.bpp, &win.img.len, &win.img.endian);

	printf("win.img.addr[10] = %d\n", win.img.addr[0]);
	// xpm file 의 texture를 win.tex.addr 에 복사 붙여놓기하였음.
	win.tex.addr = ft_strdup(win.img.addr);
	printf("win.tex.addr[10] = %d\n", win.tex.addr[0]);
	w = win.img.width;
	h = win.img.height;
	printf("w: %d\n", w); // w = 64;
	printf("h: %d\n", h); // h = 64;

	/*
	** 현재 이지미 포인터는 xpm file 을 가리키고 있으니 이미지 포인터를 부수고
	** 새 이미지 포인터를 만들어야한다. 하지만 이미지 포인터를 부수기 전에
	** 원래 이미지의 너비, 높이를 저장해야한다. 안 그러면 이미지 포인터를 부수고 나서
	** 그 값들을 알 수가 없다.
	*/
	// free(win.img.addr);
	// win.img.addr = NULL;
	mlx_destroy_image(win.mlx, win.img.ptr);
	win.img.ptr = mlx_new_image(win.mlx, w * 2, h);

	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w * 2)
		{
			// my_mlx_pixel_put(&win.img, i, j, win.tex.addr[(int)(i * w + j * 0.5)]);
			printf("%d\n", (int)(i * w + j * 0.5));
			// printf("%d\n", win.tex.addr[(int)(i * w + j)]);
			j++;
		}
		i++;
	}
	// 함수 mlx_get_data_addr 은 함수 my_mlx_put_pixel 를 적용할 때 사용
	mlx_put_image_to_window(win.mlx, win.ptr, win.img.ptr, 0, 0);
	mlx_loop(win.mlx);

	return (0);
}
