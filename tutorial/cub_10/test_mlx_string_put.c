// https://harm-smits.github.io/42docs/libs/minilibx/prototypes.html
// gcc -I ../minilibx -L ../minilibx -lmlx -framework Appkit -framework OpenGL test_mlx_pixel_put.c

// int     mlx_string_put(void *mlx_ptr, void *win_ptr, int x, int y, int color, char *string);

// Puts a string on the location (x,y) in the given window.

/*
** jikang 의 코멘트: 항상 이미지 포인터를 필요로 하는 이미지와는 다르게 함수 mlx_string_put 은 바로 쓸 수 있다.
**
*/


#include "../minilibx/mlx.h"
#include <stdlib.h>
#include <stdio.h>

# define KEY_S			1
# define KEY_D			2
# define KEY_F			3
# define KEY_G			5
# define KEY_H			4
# define KEY_J			38

typedef struct	s_param
{
	int			key;
	int			x;
	int			y;
	int			color;
	char		*str;
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
	// int keycode = vars->param.key;

	vars->param.color = create_trgb(0, 0, 255, 0);

	if (keycode == KEY_S)
		exit(0);
	if (keycode == KEY_D) // clear
		mlx_clear_window(vars->mlx, vars->win);
	if (keycode == KEY_F) // close
		mlx_destroy_window(vars->mlx, vars->win);
	if (keycode == KEY_G)
		mlx_get_color_value(vars->mlx, vars->param.color);
	if (keycode == KEY_H)
		mlx_pixel_put(vars->mlx, vars->win, vars->param.x, vars->param.y, vars->param.color);
	if (keycode == KEY_J)
	{
		vars->param.str = "cub3d";
		mlx_string_put(vars->mlx, vars->win, vars->param.x, vars->param.y, vars->param.color, vars->param.str);
	}
	return (0);
}

int					main(void)
{
	t_vars			vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 800, 480, "test");
	vars.param.x = 400;
	vars.param.y = 240;
	mlx_key_hook(vars.win, key_press, &vars); // 여기는 키를 누르는 것만 받고
	mlx_loop(vars.mlx);
}