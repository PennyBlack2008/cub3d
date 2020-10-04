// gcc -I ../minilibx -L ../minilibx -lmlx -framework Appkit -framework OpenGL main.c
/*
** https://harm-smits.github.io/42docs/libs/minilibx/hooks.html
** TEST YOUR SKILLS 의 a mouse is pressed, it will print the angle at which it moved over the window to the terminal.활용
** 1. 해상도 좌표 가운데를 (0, 0)으로 만들고 위쪽이 +, 오른쪽이 + 로 두어 마우스를 클릭할 때 마다 원점으로부터의 각도를 계산하도록 만들었음
*/

#include "../minilibx/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
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
	double		angle; // ((현재좌표) - (예전좌표)) / (예전좌표)

	// 가운데 좌표를 (0, 0)으로 하고 싶다.
	pos_x = 400;
	pos_y = 240;

	x = x - 400;
	y = (y - 240) * -1;
	if (button == 1)
	{
		printf("button was pushed\n");
		printf("current position: (x, y) = (%d, %d)\n", x, y);
		angle = atan2(y, x) * (180 / M_PI);
		printf("angle: (x, y) = (%lf)\n", angle);
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
	//							param의 역할은 알아보고 있다. --> param 의 역할: 함수 mouse_hook 에 들어가는 파라미터를 담는 구조체
	mlx_loop(vars.mlx);
}