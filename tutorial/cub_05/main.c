// 출처: https://github.com/taelee42/mlx_example
// gcc -I ../minilibx -L ../minilibx -lmlx -framework Appkit -framework OpenGL main.c

// 이 코드의 결과물은 불러온 이미지의 반은 그대로 두고 이미지의 다른 쪽은 임의로 픽셀을 수정하여 표시한다.
#include <stdio.h>
#include "../minilibx/mlx.h"

typedef struct s_img
{
	void		*ptr;
	int			*data;
	int			width;
	int			height;

	int			bpp;
	int			size_l;
	int			endian;
}				t_img;

int main()
{
		void	*mlx;
		void	*win;
		t_img	img;
		int		count_h;
		int		count_w;

		mlx = mlx_init();
		win = mlx_new_window(mlx, 500, 500, "my_mlx");
		img.ptr = mlx_xpm_file_to_image(mlx, "eagle.xpm", &img.width, &img.height);
		// img.ptr 가 img 를 못찾으면 segfault 가 난다.
		// 이 함수 mlx_xpm_file_to_image 를 통해 img.width 와 img.height 의 값이 정해진다. 구조체 t_img 에 담기게 된다.
		img.data = (int *)mlx_get_data_addr(img.ptr, &img.bpp, &img.size_l, &img.endian); // img.ptr 을 통해 width 와 height 는 이미 알고 있다.
		// img.ptr 을 통해서 width 와 height 값에 접근할 수 있어 img.data 에 1차원 배열로 픽셀을 받을 수 있는 것으로 생각한다.
		// 접근 경로는 img.ptr 을 통해 그 t_img 에 접근할 수 있고 그 구조체의 멤버에 저장된 img.width, img.height 을 통해 넓이와 높이의 값을 얻을 수 있다.
		// count_h = -1;
		// while (++count_h < img.height)
		// {
		// 	count_w = -1;
		// 	while (++count_w < img.width / 2)
		// 	{
		// 		if (count_w % 2)
		// 			img.data[count_h * img.width + count_w] = 0xFFFFFF;
		// 		else
		// 			img.data[count_h * img.width + count_w] = 0xFF0000;
		// 	}
		// }
		mlx_put_image_to_window(mlx, win, img.ptr, 50, 50);
		mlx_loop(mlx);
		return (0);
}