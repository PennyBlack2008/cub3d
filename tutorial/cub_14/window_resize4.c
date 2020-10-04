/*
** jikang 의 코멘트: W, A, S, D 를 통해 해상도를 계속 변경하는 코드입니다.
**					여기서 중요한 점은 함수 init_window 에서 var->win 에 window pointer 를 저장했는 데,
**					다시 window 의 해상도를 바꾸려면 window pointer 를 window destroy 로 부순뒤, 다시
**					코드 "var->win = mlx_new_window(var->mlx, var->window.width, var->window.height, "updated window");"
**					를 통해 다시 window pointer 를 생성해줘야한다. 쉽게 말해서 해상도를 바꾸려면 window pointer 를 갱신해줘야한다.
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../minilibx/mlx.h"

// 키 설정
# define KEY_S			1
# define KEY_D			2
# define KEY_F			3
# define KEY_G			5
# define KEY_H			4
# define KEY_W			13
# define KEY_A			0


typedef struct	s_param
{
	int			x;
	int			y;
}				t_param;

typedef struct	s_window
{
	int				width;
	int				height;
}				t_window;

typedef struct		s_vars
{
	void			*mlx;
	void			*win;
	t_param			param;
	t_window		window;
	int				update_display;
}					t_vars;

int					init_window(t_vars *var)
{
	// window 설정
	var->mlx = mlx_init();
	var->window.width = 1920;
	var->window.height = 1080;
	var->win = mlx_new_window(var->mlx, var->window.width, var->window.height, "1920 1080");
	var->update_display = 0;

	return (0);
}

int				key_press(int keycode, t_vars *var)
{
	if (keycode == KEY_W)
	{
		var->window.width = 1920;
		var->window.height = 1080;
		var->update_display = 1;
		printf("window 해상도 : FHD %d, %d\n", var->window.width, var->window.height);
	}
	if (keycode == KEY_A)
	{
		var->window.width = 1280;
		var->window.height = 720;
		var->update_display = 1;
		printf("window 해상도 : HD %d, %d\n", var->window.width, var->window.height);
	}
	if (keycode == KEY_S)
	{
		var->window.width = 1280;
		var->window.height = 800;
		var->update_display = 1;
		printf("window 해상도 : WXGA %d, %d\n", var->window.width, var->window.height);
	}
	if (keycode == KEY_D)
	{
		var->window.width = 640;
		var->window.height = 480;
		var->update_display = 1;
		printf("window 해상도 : VGA %d, %d\n", var->window.width, var->window.height);
	}
	if (keycode == KEY_H)
		exit(0);

	return (0);
}

void				update_window(t_vars *var)
{
	mlx_destroy_window(var->mlx, var->win);
	var->win = mlx_new_window(var->mlx, var->window.width, var->window.height, "updated window");
	mlx_key_hook(var->win, &key_press, var); // 여기는 키를 누르는 것만 받고
}

int     main_loop(t_vars *var)
{
	if (var->update_display)
	{
		update_window(var);
		var->update_display = 0;
	}
	var->update_display = 0;
	return (0);
}

int     main(void)
{
	t_vars	var;

	// window 설정
	init_window(&var);

	mlx_key_hook(var.win, key_press, &var); // 여기는 키를 누르는 것만 받고
	mlx_loop_hook(var.mlx, &main_loop, &var);
	mlx_loop(var.mlx);

	return (0);
}