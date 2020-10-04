// 창을 여러개 띄우는 시도. seg fault 및 bus error

/*
** jikang 의 코멘트: window를 여러 창을 띄우는 코드를 시도했지만 segfault 로 성공하지 못했다.
*/

#include "../libft/libft.h"
#include "../minilibx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_window
{
	void *ptr;
	int width;
	int height;
}				t_window;

int		init_window(void *mlx, t_window *win)
{
	win->ptr = mlx_new_window(mlx, 300, 300, "veryluckyjinwoo");
	return (0);
}

int main(void)
{
	// mlx 포인터 생성 // mlx를 하나로 통일해도 동일한 증상
	void *mlx_1;			mlx_1 = mlx_init();
	void *mlx_2;			mlx_2 = mlx_init();
	void *mlx_3;			mlx_3 = mlx_init();


	t_window *win_1;
	t_window *win_2;
	t_window *win_3;

	init_window(mlx_1, win_1);
	init_window(mlx_2, win_2);
	init_window(mlx_3, win_3);

	mlx_loop(mlx_1);
	mlx_loop(mlx_2);
	mlx_loop(mlx_3);
}