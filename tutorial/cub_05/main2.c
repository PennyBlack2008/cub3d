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
	int			width;
	int			height;
}					t_img;

typedef struct		s_tex
{
	t_img			img;
}					t_tex;

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
	int				i, j, k;
	char			*cpy;

	win.mlx = mlx_init();
	win.ptr = mlx_new_window(win.mlx, 500, 500, "veryluckymanjinwoo");
	win.img.ptr = mlx_xpm_file_to_image(win.mlx, "eagle.xpm", &win.img.width, &win.img.height);
	win.img.addr = mlx_get_data_addr(win.img.ptr, &win.img.bpp, &win.img.len, &win.img.endian);

	cpy = ft_strdup(win.img.addr); // 원본을 복사 붙여넣기
	w = win.img.width; // 원본의 너비
	win.img.width *= 2; // 길이 두배로 늘리자

	printf("이제 더 커진 너비: %d\n", win.img.width);
	printf("높이: %d\n", win.img.height);
	printf("높이: %d\n", win.img.len);
	printf("%s\n", win.img.addr);
	i = 0; // count_h
	k = -1;
	while (i < win.img.height)
	{
		j = 0; // count_w
		while (j < w)
		{
			win.img.addr[++k] = cpy[i * w + j];
			win.img.addr[++k] = cpy[i * w + j];
			printf("%d\n", win.img.addr[k]);
			j++;
			// k++;
		}
		i++;
	}
	// 함수 mlx_get_data_addr 은 함수 my_mlx_put_pixel 를 적용할 때 사용
	mlx_put_image_to_window(win.mlx, win.ptr, win.img.ptr, 0, 0);
	mlx_loop(win.mlx);

	return (0);
}
