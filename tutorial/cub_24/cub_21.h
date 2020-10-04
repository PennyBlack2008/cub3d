#ifndef _CUB_21_H_
# define _CUB_21_H_

#include "../get_next_line/get_next_line.h"
#include "../libft/libft.h"
#include "../minilibx/mlx.h"
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// WIN SPEC
#define WIN_WIDTH 1000
#define WIN_HEIGHT 1000
#define fov 60

// DEBUG
#define ERROR 0
#define SUCCESS 1
#define FILEEND 0

// KEY

# define KEY_W			13
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2

# define KEY_LEFT		123
# define KEY_RIGHT		124

# define KEY_F			3
# define KEY_G			5
# define KEY_H			4

# define KEY_ESC		53

/*
** Center of the Projection Plane = (160,100)
** Distance to the Projection Plane = 277 units
** Angle between subsequent rays = 60/320 degrees
*/


typedef struct			s_player
{
	int					color;

	// 화살표 각도(시야각)
	double				ang;
	int					pdi;
	int					pdj;

	// player 위치
	int					x;
	int					y;
	char*				str_KEY_W; // 빨간색 끝에 적어줄 글자
	char*				str_KEY_D; // 파란색 끝에 적어줄 글자
}						t_player;

typedef struct  s_img
{
    void        *ptr;
    char        *addr; // 이 변수에 image 픽셀의 색을 넣어주는 것이 이미지를 만드는 것이다.
    int         bits_per_pixel;
    int         line_length;
    int         endian;

	int			x;
	int			y;
	int			tile_color;
}               t_img;

typedef struct	s_map
{
	char		**map;
	int			i;
	int			j;
}				t_map;


typedef struct 			s_win
{
	void				*mlx;
	void				*win;
	int					R_width;
	int					R_height;
	t_img				img;
	t_map				map;
	t_player			player;
}						t_win;

void					my_mlx_pixel_put(t_img *img, int x, int y, int color);
int						draw_player(t_win *w);
int						draw_grid(t_win *w);
int						draw_background(t_win *w);

#endif