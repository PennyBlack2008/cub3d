// https://harm-smits.github.io/42docs/libs/minilibx/prototypes.html
// gcc -I ../minilibx -L ../minilibx -lmlx -framework Appkit -framework OpenGL test_mlx_get_color_value.c

/*
** uint    mlx_get_color_value(void *mlx_ptr, int color);
** Get the color value accordingly from a int. This is useful for converting a self-declared int before writing it to certain bits.
*/

/*
** jikang 의 코멘트: mlx_get_color_value 가 어떤 기능을 가지고 있는 지 알아보기위해 만든 코드인데.... 모르겠다.
**
*/

#include "../minilibx/mlx.h"
#include <stdlib.h>
#include <stdio.h>

# define KEY_S			1
# define KEY_D			2
# define KEY_F			3
# define KEY_G			5

typedef struct	s_param
{
	int			key;
	int			x;
	int			y;
	int			color;
}				t_param;

typedef struct		s_vars
{
	void			*mlx;
	void			*win;
	t_param			param;
}					t_vars;

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

int				key_press(int keycode, t_vars *vars)
{
	vars->param.color = create_trgb(0, 0, 255, 0);

	if (keycode == KEY_S)
		exit(0);
	if (keycode == KEY_D)
		mlx_clear_window(vars->mlx, vars->win);
	if (keycode == KEY_F)
		mlx_destroy_window(vars->mlx, vars->win);
	if (keycode == KEY_G)
		mlx_get_color_value(vars->mlx, vars->param.color); // 이 함수의 역할을 모르겠다.
	return (0);
}

int					main(void)
{
	t_vars			vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 800, 480, "test");

	mlx_key_hook(vars.win, key_press, &vars); // 여기는 키를 누르는 것만 받고
	mlx_loop(vars.mlx);
}