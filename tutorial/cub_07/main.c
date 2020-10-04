// 출처: https://github.com/taelee42/mlx_example
// gcc -I ../minilibx -L ../minilibx -lmlx -framework Appkit -framework OpenGL main.c

/*
** https://harm-smits.github.io/42docs/libs/minilibx/hooks.html
** TEST YOUR SKILLS 의 a key is pressed, it will print the key code in the terminal.활용
** 1. 함수 mlx_hook 의 파라미터의 *param 활용법을 알 수 있었다.
*/
#include "../minilibx/mlx.h"
#include <stdio.h>
#include <stdlib.h>

#define X_EVENT_KEY_PRESS		2
#define X_EVENT_KEY_release		3
#define X_EVENT_KEY_EXIT		17

# define KEY_ESC		53
# define KEY_Q			12
# define KEY_W			13
# define KEY_E			14
# define KEY_R			15
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2

# define ROWS 11 // 행의 갯수
# define COLS 15 // 열의 갯수

typedef struct	s_param{
	int		x;
	int		y;
}				t_param;

typedef struct	s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
}				t_img;

void			param_init(t_param *param)
{
	param->x = 0; // W
	param->y = 0; // S
}

// 이 함수에 파라미터로 param 이 담기긴 하지만, 함수 key_press 가 호출될 때마다 이 param 에 정보를 담아도 되고
// 그렇지 않아도 무방하다.
int				key_press(int keycode, t_param *param)
{
	static int a = 0;

	if (keycode == KEY_W)
	{
		param->x++;
		printf("\nKEY_W was pressed %d times\n", param->x);
	}
	else if (keycode == KEY_S)
	{
		param->y++;
		printf("\nKEY_S was pressed %d times\n", param->y);
	}
	else if (keycode == KEY_ESC)
	{
		printf("\nKEY_ESC was pressed, exit\n");
		exit(0);
	}
	return (0);
}

int			main(void)
{
	void		*mlx;
	void		*win;
	t_param		param;

	param_init(&param);
	mlx = mlx_init();
	win = mlx_new_window(mlx, 500, 500, "mlx_project");

	mlx_mouse_hook(win, &key_press, &param);
	// mlx_hook(win, X_EVENT_KEY_PRESS, 0, &key_press, &param);
	mlx_loop(mlx);
}