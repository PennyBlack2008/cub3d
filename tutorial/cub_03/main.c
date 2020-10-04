// 출처: https://github.com/taelee42/mlx_example

// gcc -I ../minilibx -L ../minilibx -lmlx -framework Appkit -framework OpenGL main.c

// 오류 수정 by Ykoh
#include "../minilibx/mlx.h"
#include <stdio.h>

typedef struct s_img
{
	void		*ptr;
	int			*data;
	int			width;
	int			height;


	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win;
}				t_mlx;

int main()
{
		t_mlx *mlx;
		t_img img;

		mlx->mlx_ptr = mlx_init(); // mlx 함수들 시작(나는 fd 같은 존재로 이해하고 있음)
		mlx->win = mlx_new_window(mlx->mlx_ptr, 500, 500, "my_mlx");

		// mlx_xpm_file_to_image 함수는 image의 크기를 img_width, img_height에 담고, 반환 값을 변수 img에 담는다.
		img.ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "eagle.xpm", &img.width, &img.height);

		// mlx_put_image_to_window는 image의 위치를 정해준다.
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, img.ptr, 150, 150);
		mlx_loop(mlx->mlx_ptr);
		return (0);
}