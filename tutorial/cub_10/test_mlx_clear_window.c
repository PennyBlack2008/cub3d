// https://harm-smits.github.io/42docs/libs/minilibx/prototypes.html
// gcc -I ../minilibx -L ../minilibx -lmlx -framework Appkit -framework OpenGL test_mlx_clear_window.c

/*
** int     mlx_clear_window(void *mlx_ptr, void *win_ptr);
** Clears the current window. This is not a recommended function to use.
** Instead, it is recommended to use the function mlx_put_image_to_window with a recycled image that you have cleared.
*/

// jikang 의 코멘트: 이거 뭐하는 건지 모르겠다. 눈에 보이는 결과는 아무것도 없다.
#include "../minilibx/mlx.h"
#include <stdlib.h>
#include <stdio.h>

# define KEY_S			1
# define KEY_D			2

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

int				key_press(int keycode, t_vars *vars) // key_hook(int keycode,void *param) 형식을 지켜주기 위해 포인터로 해야함
{
	if (keycode == KEY_S)
		exit(0);
	if (keycode == KEY_D)
		mlx_clear_window(vars->mlx, vars->win);
	return (0);
}

int					main(void)
{
	t_vars			vars;
	t_param			param;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 800, 480, "test");

	mlx_key_hook(vars.win, key_press, &vars); // key_hook(int keycode,void *param) 형식을 지켜주기 위해 포인터로 해야함
	mlx_loop(vars.mlx);
}