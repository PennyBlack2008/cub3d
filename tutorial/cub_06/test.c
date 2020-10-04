// 출처: https://github.com/taelee42/mlx_example
// gcc -I ../minilibx -L ../minilibx -lmlx -framework Appkit -framework OpenGL test.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../minilibx/mlx.h"

#define X_EVENT_KEY_PRESS		2
#define X_EVENT_KEY_EXIT		17

#define KEY_ESC					53
#define TILE_SIZE				32
#define ROWS					11
#define COLS					15
#define WIDTH COLS * TILE_SIZE
#define HEIGHT ROWS * TILE_SIZE
#define TO_COORD(X, Y) ((int)floor(Y) * WIDTH + (int)floor(X))

typedef struct					s_img
{
	void						*ptr;
	char						*addr;
	int							size_l;
	int							bpp;
	int							endian;
}								t_img;

typedef struct					s_game
{
	void						*mlx;
	void						*win;
	t_img						img;
	int							map[ROWS][COLS];
}								t_game;

void					my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char				*dst;

	dst = img->addr + (y * img->size_l + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
	// printf("%d, %d\n", x, y);
}

void							draw_line(t_game *game, double x1, double y1, double x2, double y2)
{
	double						deltaX;
	double						deltaY;
	double						step;

	deltaX = x2 - x1;
	deltaY = y2 - y1;
	step = (fabs(deltaX) > fabs(deltaY)) ? fabs(deltaX) : fabs(deltaY);
	deltaX /= step;
	deltaY /= step;

	while (fabs(x2 - x1) > 0.01 || fabs(y2 -y1) > 0.01)
	{
		my_mlx_pixel_put(&game->img, x1, y1, 0xb3b3b3);
		x1 += deltaX;
		y1 += deltaY;
	}
}

void							draw_lines(t_game *game)
{
	int							i;
	int							j;

	i = 0;
	while (i < COLS)
	{
		// 세로로 긋는 선
		draw_line(game, i * TILE_SIZE, 0, i * TILE_SIZE, HEIGHT);
		i++;
	}
	// 마지막 세로 선
	draw_line(game, COLS * TILE_SIZE - 1, 0,  COLS * TILE_SIZE - 1, HEIGHT);
	j = 0;
	while (j < ROWS)
	{
		// 가로로 긋는 선
		draw_line(game, 0, j * TILE_SIZE, WIDTH, j * TILE_SIZE);
		j++;
	}
	// 마지막 가로 선
	draw_line(game, 0, ROWS * TILE_SIZE - 1, WIDTH, ROWS * TILE_SIZE - 1);
}

void							draw_rectangle(t_game *game, int x, int y)
{
	int							i;
	int							j;

	x *= TILE_SIZE;
	y *= TILE_SIZE;
	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			my_mlx_pixel_put(&game->img, y + i, x + j, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

void							draw_rectangles(t_game *game)
{
	int							i;
	int							j;

	i = 0;
	while (i < ROWS)
	{
		j = 0;
		while (j < COLS)
		{
			if (game->map[i][j] == 1)
				draw_rectangle(game, j, i);
			j++;
		}
		i++;
	}
}

int								deal_key(int key_code, t_game *game)
{
	if (key_code == KEY_ESC)
		exit(0);
	return (0);
}

int								close(t_game *game)
{
	exit(0);
}

void							game_init(t_game *game)
{
	int map[ROWS][COLS] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};
	memcpy(game->map, map, sizeof(int) * ROWS * COLS);
}

void							window_init(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "mlx");
}

void							img_init(t_game *game)
{
	game->img.ptr = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img.addr = (char *)mlx_get_data_addr(game->img.ptr, &game->img.bpp, &game->img.size_l, &game->img.endian);
}

int								main_loop(t_game *game)
{
	draw_rectangles(game);
	draw_lines(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
	return (0);
}

int								main(void)
{
	t_game						game;

	game_init(&game);
	window_init(&game);
	img_init(&game);
	mlx_hook(game.win, X_EVENT_KEY_PRESS, 0, &deal_key, &game);
	mlx_hook(game.win, X_EVENT_KEY_EXIT, 0, &close, &game);
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_loop(game.mlx);
}
