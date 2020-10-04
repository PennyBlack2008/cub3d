// gcc -I ../minilibx -L ../minilibx -lmlx -framework Appkit -framework OpenGL main.c

/*
** https://harm-smits.github.io/42docs/libs/minilibx/hooks.html
** the mouse if moved, it will print the current position of that mouse in the terminal.활용
** 마우스의 버튼 및 움직임의 값을 받아오는 함수 mlx_mouse_hook 을 통해 button, x, y 의 값을 받아 터미널에 출력해보는 예제
*/

#include "../minilibx/mlx.h"
#include <stdlib.h>
#include <stdio.h>
# define KEY_S			1

typedef struct	s_vars
{
	void		*mlx;
	void		*win;
}				t_vars;

typedef struct	s_param
{
	int			key;
	int			x;
	int			y;
}				t_param;

int				close(int keycode, t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

int				key_press(int keycode)
{
	if (keycode == KEY_S) // Action when W key pressed
		exit(0);
	return (0);
}

int				mouse_hook(int button, int x, int y, void *param)
{
	int			pos_x;
	int			pos_y;
	if (button == 1)
	{
		printf("button was pushed\n");
		printf("current position: (x, y) = (%d, %d)\n", x, y);
	}
	return (0);
}

int				main(void)
{
	t_vars		vars;
	t_param		param;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 800, 480, "test");
	mlx_key_hook(vars.win, &key_press, &param.key);
	mlx_mouse_hook(vars.win, &mouse_hook, &param);
	// 함수 mlx_mouse_hook 으로부터 실시간으로 mouse_hook의 함수에서 x, y의 위치를 얻을 수 있다.
	// mlx_mouse_hook 의 역할: 마우스의 버튼이 클릭되면 함수 mouse_hook의 첫 번째 파라미터인 button 에 1 을 저장한다.
	//							마우스의 위치를 mouse_hook 의 두, 세 번째 파라미터인 x, y에 각각의 좌표값을 저장한다.
	//							param의 역할은 알아보고 있다.
	mlx_loop(vars.mlx);
}