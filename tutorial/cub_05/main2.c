#include <stdio.h>
#include "../minilibx/mlx.h"

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
}					t_win;

int					main()
{
	t_win			win;
	int				h;
	int				w;

	win.mlx = mlx_init();
	win.ptr = mlx_new_window(win.mlx, 500, 500, "veryluckymanjinwoo");
	win.img.ptr = mlx_xpm_file_to_image(win.mlx, "eagle.xpm", &win.img.width, &win.img.height);
	// win.img.addr = mlx_get_data_addr(win.img.ptr, &win.img.bpp, &win.img.len, &win.img.endian);
	// 함수 mlx_get_data_addr 은 함수 my_mlx_put_pixel 를 적용할 때 사용
	mlx_put_image_to_window(win.mlx, win.ptr, win.img.ptr, 0, 0);
	mlx_loop(win.mlx);

	return (0);
}
