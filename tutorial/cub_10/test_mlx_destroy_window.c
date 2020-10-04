// https://harm-smits.github.io/42docs/libs/minilibx/prototypes.html
// gcc -I ../minilibx -L ../minilibx -lmlx -framework Appkit -framework OpenGL test_mlx_destroy_window.c

/*
** int     mlx_destroy_window(void *mlx_ptr, void *win_ptr);
** Destroys a window instance accordingly.
*/


/*
** jikang 의 코멘트: S 키는 프로그램 종료, D 키는 mlx_clear_window, F 키는 mlx_destroy_window 이다.
**					S 키는 프로그램과 함께 mlx window 창도 종료되지만, F 키는 프로그램이 종료되지 않고 window 창만 종료된다.
*/
#include "../minilibx/mlx.h"
#include <stdlib.h>
#include <stdio.h>

# define KEY_S			1
# define KEY_D			2
# define KEY_F			3

typedef struct	s_param
{
	int			key;
	int			x;
	int			y;
}				t_param;

typedef struct		s_vars
{
	void			*mlx;
	void			*win;
	t_param			param;
}					t_vars;

int				key_press(int keycode, t_vars *vars)
{
	if (keycode == KEY_S)
		exit(0);
	if (keycode == KEY_D)
		mlx_clear_window(vars->mlx, vars->win);
	if (keycode == KEY_F)
		mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

int					main(void)
{
	t_vars			vars;
	t_param			param;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 800, 480, "test");

	mlx_key_hook(vars.win, key_press, &vars);
	mlx_loop(vars.mlx);
}