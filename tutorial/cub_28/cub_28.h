#ifndef _CUB_28_H_
# define _CUB_28_H_

#include "../get_next_line/get_next_line.h"
#include "../libft/libft.h"
#include "../minilibx/mlx.h"
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define TILE_LENGTH 100
#define WALL 49 // ascii #1
#define NOT_WALL 48 // ascii #0

typedef struct		s_plot
{
	double			x;
	double			y;
}					t_plot;

typedef struct		s_img
{
	void			*ptr;
	char			*addr; // 이 변수에 image 픽셀의 색을 넣어주는 것이 이미지를 만드는 것이다.
	int     	    bits_per_pixel;
	int         	line_length;
	int				endian;

	int				x;
	int				y;
	int				tile_color;

}					t_img;

typedef struct		s_ray
{
	double			ang;
}					t_ray;

typedef struct		s_map
{
	char			**map;
}					t_map;

typedef struct		s_player
{
	int				x;
	int				y;
	double			ang;
}					t_player;


typedef struct		s_win
{
	void			*mlx;
	void			*ptr;
	int				R_width;
	int				R_height;
	double			fov;
	t_img			img;
	t_map			map;
	t_player		player;
}					t_win;

void					my_mlx_pixel_put(t_img *img, int x, int y, int color);
void					map_init(t_win *w);
void					draw_map(t_win *w);
int						is_wall(double x, double y, t_win *w);
void					draw_rectangle(t_win *w, int x, int y, int color);
void					draw_line(int p1_x, int p1_y, int p2_x, int p2_y, int color, t_win *w);
void					draw_rays(t_win *w);
int						is_wall_ray(double x, double y, t_ray *r, t_win *w);

#endif