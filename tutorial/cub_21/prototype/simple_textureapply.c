#include "../libft/libft.h"
#include "../minilibx/mlx.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define R_width 500
#define R_height 500

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

typedef struct	s_player
{
	double		pos_x;
	double		pos_y;
}				t_player;

typedef struct	s_win
{
	void		*mlx;
	void		*ptr; // window pointer
	t_img		img;
	t_player	player;
}				t_win;

int main()
{
	t_win	win;
	int		i, j;		i = 0;		j = 100;

	win.mlx = mlx_init(); // mlx 함수들 시작(나는 fd 같은 존재로 이해하고 있음)
	win.ptr = mlx_new_window(win.mlx, R_width, R_height, "my_mlx");
	win.img.ptr = mlx_xpm_file_to_image(win.mlx, "../../practice_note/textures/wall_1.xpm", &win.img.width, &win.img.height);

	// mlx_xpm_file_to_image 함수는 image의 크기를 img_width, img_height에 담고, 반환 값을 변수 img에 담는다.
	while (j < R_height / 3)
	{
		while (i < R_width)
		{
			mlx_put_image_to_window(win.mlx, win.ptr, win.img.ptr, i, j);
			i += 64;
		}
		j += 64;
		i = 0;
	}

	// mlx_put_image_to_window는 image의 위치를 정해준다.
	mlx_loop(win.mlx);

	return (0);
}