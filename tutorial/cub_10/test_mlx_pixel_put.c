// https://harm-smits.github.io/42docs/libs/minilibx/prototypes.html
// gcc -I ../minilibx -L ../minilibx -lmlx -framework Appkit -framework OpenGL test_mlx_pixel_put.c

// int     mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color);

// Puts a pixel on the screen. This function is NOT recommended to be used.
// It will lock the window output, force a refresh and a recalculation.
// It is therefore suggested to render a image and push that using the mlx_put_image_to_window function.
// You can find more about that in the Getting Started chapter.

/*
** jikang 의 코멘트: 함수 mlx_pixel_put 는 사용하지말라고 하네요. 어떻게 사용해야하는지 아직 모르겠습니다.
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
	{
		// printf("%d %d\n",vars->param.x, vars->param.y);
		mlx_pixel_put(vars->mlx, vars->win, vars->param.x, vars->param.y, vars->param.color);
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