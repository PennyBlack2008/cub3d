#include "/Users/jikang/Documents/Pennymannibanni/42cursus/cub3D/minilibx_opengl_20191021/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
# define X 0
# define Y 1
typedef struct  s_data {
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	struct s_animate	*ani;
	struct s_position	*pos;
}				t_data;
typedef struct s_position{
	int pos[2]; 
	int mov[2];
}				t_position;
typedef struct s_second{
	int start;
	int end;
}				t_second;
typedef struct s_animate{
	int color;
	int count;
}				t_animate;
int	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	// printf("%p\n", data->addr);
	// printf("%d\n", data->bits_per_pixel/8);
	// printf("%d\n", data->line_length);
    *((unsigned int*)dst) = color;
	return (3);
}
int	loop_hook_easy(t_data *ptr)
{
	// t_data *ptr = param;
	int num;
	num = 300;
	//ptr->ani->color -= 0x000101;
	while (ptr->pos->mov[Y] > 0)
	{
		num = 0;
		ptr->pos->mov[X]++;
		while (num < ptr->pos->mov[X])
		{
			my_mlx_pixel_put(ptr, ptr->pos->pos[X] + num, ptr->pos->pos[Y] + ptr->pos->mov[Y], ptr->ani->color);
			num++;
		}
		ptr->pos->mov[Y]--;
	}
	ptr->pos->mov[X] = 0;
	ptr->pos->mov[Y] = 200;
	return (1);
}
int mlx_exit(int keycode, void *param)
{
	t_data *img = param;
	printf("click\n");
	if(keycode == 0)
	{
		printf("a\n");
	}
	else if (keycode == 10)
	{
		printf("mouse\n");
	}
	else if(keycode == 53)
	{
		printf("esc\n");
		mlx_destroy_window(img->mlx, img->win);
		exit(0);
	}
	else if (keycode == 1)
	{
		loop_hook_easy(param);
	}
	return (1);
}
int mouse_hook(int x, int y, void *param)
{
	static char in_out = 0;
	// printf("%d %d\n", x, y);
	if ((x > 0 && x < 800) && (y > 0 && y < 800) && in_out == 0)
	{
		printf("hi\n");
		in_out = 1;
	}
	else if ((!(x > 0 && x < 800) || !(y > 0 && y < 800)) && in_out == 1)
	{
		printf("bye\n");
		in_out = 0;
	}
	// printf("%p\n",param);
	return (1);
}
int mouse_release(int button, int x, int y, void* param)
{
	t_second *my_time = param;
	my_time->end = 0;
	if (button == 1)
	{
		my_time->end = time(0);
		// printf("%d\n", time(NULL));
		// printf("time end ; %d\n", my_time->end);
		if (my_time->end - my_time->start > 2)
		{
			printf("click my_time is 2 second over\n");
		}
		// printf("interval : %d\n", (int)(my_time->end - my_time->start));
	}
	// printf("button_release %d\n",button);
	return (1);
}
int mouse_press(int button, int x, int y, void* param)
{
	t_second *my_time = param;
	my_time->start = 0;
	if (button == 1)
	{
		my_time->start = time(0);
		// printf("%d\n", time(0));
		// printf("time start ; %d\n", my_time->start);
	}
	// printf("button_press %d\n",button);
	// printf("address : %d\n", param);
	return (1);
}
int	main(void)
{
    void    *mlx;
    void    *mlx_win;
	int pos[2]; 
	int mov[2];
	int start;
	int end;
    t_data  img;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1000, 1000, "Hello world!"); // 해상도
	img.win = mlx_win;
	img.mlx = mlx;
	img.img = mlx_new_image(mlx, 1000, 1000); // 크기
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
									&img.endian);
	printf("-----------%p-------------\n", img.img);
	int temp_x;
	int temp_y;
	int num = 0;
	int scale = mov[Y];
	int color = 0x99ccff;
	t_animate ani;
	t_position posit;
	//직각삼각형
	pos[X] = 0; pos[Y] = 0;
	mov[X] = 0; mov[Y] = 200;
	img.ani = &ani;
	img.pos = &posit;
	img.pos->mov[X] = mov[X]; 
	img.pos->mov[Y] = mov[Y];
	img.pos->pos[X] = pos[X];
	img.pos->pos[Y] = pos[Y];
	ani.color = color;
	while (mov[Y] > 0)
	{
		num = 0;
		mov[X]++;
		while (num < mov[X])
		{
			my_mlx_pixel_put(&img, pos[X] + num, pos[Y] + mov[Y], 0x99ccff);
			num++;
		}
		mov[Y]--;
	}
	printf("loop_main : %p\n", &img);
	//피라미드 삼각형
	//int형에서는 홀수만 가능
	// int start_x = (mov[Y] - 1) / 2;
	// int i = 0;
	// int temp;
	// int count;
	// pos[X] = 500; pos[Y] = 500;
	// mov[X] = 0; mov[Y] = 200;
	// img.ani = &ani;
	// img.pos = &posit;
	// img.pos->mov[X] = mov[X]; 
	// img.pos->mov[Y] = mov[Y];
	// img.pos->pos[X] = pos[X];
	// img.pos->pos[Y] = pos[Y];
	// ani.color = color;
	// while (mov[Y] > 0)
	// {
	// 	count = 2 * (400 - mov[Y]) + 1;
	// 	i = 0;
	// 	if (mov[Y] % 2 == 0)
	// 		ani.color -= 0x000001;
	// 	while (i < count)
	// 	{
	// 		my_mlx_pixel_put(&img, pos[X] + start_x + i, pos[Y] + mov[Y], ani.color);
	// 		i++;
	// 	}
	// 	start_x--;
	// 	mov[Y]--;
	// }
	t_second play_time;
	printf("play_time : %p\n", &play_time);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 500, 500);
	//keyboard_event
	mlx_hook(img.win, 2, 0, mlx_exit, &img);
	//mouse_event
	mlx_hook(img.win, 4, 0, mouse_press, &play_time);
	mlx_hook(img.win, 5, 0, mouse_release, &play_time);
	mlx_hook(img.win, 6, 0, mouse_hook, &ani);
	// mlx_loop_hook(img.mlx, loop_hook_easy, &img);
	// mlx_hook(img.win, 25, 0, 0, &img);
	printf("main : %p\n", &img);
	// mlx_hook(img.win, 6, 0, mlx_mouse_hook, &img);
	mlx_loop(mlx);
}