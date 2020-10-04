// 출처: https://github.com/taelee42/mlx_example
// gcc -I ../minilibx -L ../minilibx -lmlx -framework Appkit -framework OpenGL main.c

// 이 예제에서는 이미지를 만드는 법에 대해서 알 수 있게 해준다.
// 하지만 이미지를 로딩하는 방법이 빠져있으므로 따로 학습해야한다.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../minilibx/mlx.h"

// 이 밑에 두 개의 define 은 함수 mlx_hook 에 쓰인다. mlx_hook 에 어떤 종류의 입력이 들어갈지 정해주는 코드이다.
#define X_EVENT_KEY_PRESS		2
#define X_EVENT_KEY_EXIT		17

#define KEY_ESC			53 // 53번 코드 -> 'ESC'

# define TILE_SIZE 32 // 타일의 크기 정하는 것
# define ROWS 11 // 행의 갯수
# define COLS 15 // 열의 갯수
# define WIDTH COLS * TILE_SIZE // WIDTH = COLS * TILES_SIZE
# define HEIGHT ROWS * TILE_SIZE // HEIGHT = ROWS * TILES_SIZE

typedef struct	s_img
{
	void	*ptr;
	char	*addr;

	int		size_l;
	int		bpp;
	int		endian;
}				t_img;

// game의 구조체인데, 이 game의 구조체 안에 img 구조체가 있다. 그리고 map이 있는 데 이게 무슨말인지 모르겠다.
// game을 뭐라고 상상하면 간단하게 생각할 수 있을까? game_init 함수를 공부해보면 될 것같다.
typedef struct	s_game
{
	void	*mlx;
	void	*win;
	t_img	img;

	int		map[ROWS][COLS];
	// 지금 드는 생각은 함수 game_init 의 2 차원 배열 map 을 받아오는 것같다. 0, 1 을 받아 game 구조체에
	// map 의 표현을 저장한다.
}				t_game;

void					my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char				*dst;

	dst = img->addr + (y * img->size_l + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

// Draw the line by DDA algorithm
// 두 점을 정의하여 선을 만드는 함수인 듯. fabs 는 double type 에 대한 절대값을 반환.
void	draw_line(t_game *game, double x1, double y1, double x2, double y2)
{
	double	deltaX;
	double	deltaY;
	double	step;

	deltaX = x2 - x1; // 두 점의 x 좌표의 차
	deltaY = y2 - y1; // 두 점의 y 좌표의 차
	step = (fabs(deltaX) > fabs(deltaY)) ? fabs(deltaX) : fabs(deltaY); // X 의 차와 Y 의 차 중 큰 값을 step 에서 받는다.
	// deltaX 와 deltaY 중 하나는 자기 자신을 나누었음으로 1 일 것이다.
	deltaX /= step; // 가장 차이가 큰 값을 나누어서 넣는다.
	deltaY /= step;
	while (fabs(x2 - x1) > 0.01 || fabs(y2 - y1) > 0.01) // 왜 하필이면 0.01 일 까? 1을 넣거나 0.001을 넣어도 값은 그대로이다.
	{
		my_mlx_pixel_put(&game->img, x1, y1, 0xb3b3b3);
		// game->img.addr[TO_COORD(x1, y1)] = 0xb3b3b3; // 여기서 TO_COORD 는 무슨 역할을 할 까? 일단 0xb3b3b3 은 회색.
		// 회색이니 일단 이 과정은 중간 중간 타일 사이 격자로 들어가는 곳에 회색을 칠하는 것으로 해석할 수 있다.
		x1 += deltaX;
		y1 += deltaY;
	}
}

// draw_line를 그리는 draw_lines는 무슨 역할을 할 까?
// 일단은 이 함수를 통해서 game 은 으레 있는(아이덴티티) mlx, win 포인터를 지니고 있고 이미지 구조체와 map 의 2차원 좌표를 갖고 있다.
// 이 함수가 특이한게 map 처리하려면 이차원 배열이라 while 문 안에 COLS 처리한 다음 ROWS 처리하는 식으로 해야 할 것 같은데,
// while 문이 각각 COLS, ROWS 독립적으로 계산되어 있어 어떻게 이해해야할 지 고민이다.
void 	draw_lines(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < COLS)
	{
		// 세로로 긋는 선, x 좌표는 변하지 않고 y 좌표만 변했으므로
		draw_line(game, i * TILE_SIZE, 0, i * TILE_SIZE, HEIGHT);
		i++;
	}
	// 마지막 세로 선, 특이한 점은 COLS * TILE_SIZE - 1 를 했다는 점이다.
	draw_line(game, COLS * TILE_SIZE - 1, 0, COLS * TILE_SIZE - 1, HEIGHT);
	j = 0;
	while (j < ROWS)
	{
		// 가로로 긋는 선.
		draw_line(game, 0, j * TILE_SIZE, WIDTH, j * TILE_SIZE);
		j++;
	}
	// 마지막 가로 선, 특이한 점은 ROWS * TILE_SIZE - 1 을 했다는 점이다. 왜 그러는 지는 모르겠다.
	draw_line(game, 0, ROWS * TILE_SIZE - 1, WIDTH, ROWS * TILE_SIZE - 1);
}

// 하얀색 사각형을 그리는 함수, 검정 사각형은 검정바탕에 경계선만 그어주면 된다.
// 그래서 이 함수에서는 하얀 사각형만 그려준다.
void	draw_rectangle(t_game *game, int x, int y)
{
	int i;
	int j;

	x *= TILE_SIZE;
	y *= TILE_SIZE;
	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			my_mlx_pixel_put(&game->img, y + i, x + j, 0xFFFFFF);
			// game->img.data[(y  + i) * WIDTH + x + j] = 0xFFFFFF; // 하얀 색을 그린다.
			// 여기서 계산 법이 이해가 되지 않는다. y + i 라니... 그리고 x + j ???
			// 예전에 고민 했던 1 차원 배열로 2 차원 표현을 하는 cub_04 의 예제와 같은 것같다.
			// 이것을 이해하기보다는 외워야 활용하기 편할 것같다.
			j++;
		}
		i++;
	}
}

// i, j 에 따라 값을 증가시키면서  사각형들을 그린다.
void	draw_rectangles(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < ROWS)
	{
		j = 0;
		while (j < COLS)
		{
			if (game->map[i][j] == 1) // game_init 으로부터 저장된 2 차원 배열 map 이 1 이면 사각형을 그리는 함수 작동
				draw_rectangle(game, i, j);
			j++;
		}
		i++;
	}
}

// 이 함수를 통해서 key 를 입력받아 설정한 action 을 하도록 할 수 있다.
int		deal_key(int key_code, t_game *game)
{
	if (key_code == KEY_ESC)
		exit(0);
	return (0);
}

// 직접 exit(0) code 를 사용하기보다는 close 함수를 만들어 사용한다.
int 	close(t_game *game)
{
		exit(0);
}

void	game_init(t_game *game)
{
	// 여기서 1 은 흰 색, 0 은 검정색이다.
	int map[ROWS][COLS] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};
	// 위에 정의된 2 차원 배열 map 을 구조체 game 의 map 에 저장해주는 과정이다.
	memcpy(game->map, map, sizeof(int) * ROWS * COLS);
}

// window 창을 띄우는 함수, game 구조체 안에 있는 mlx, win 포인터에 정체성을 부여해준다.
void	window_init(t_game *game)
{
	game->mlx = mlx_init(); // 여기서 mlx 에 mlx_init 을 해주고 마지막에 mlx_loop(game.mlx); 를 해준다.
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "mlx 42");
}

// image 를 정체성을 만들어주고 game 의 이미지 관련 구조체인 img.img 와 img.data 에 정체성을 넣어준다.
void	img_init(t_game *game)
{
	game->img.ptr = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.ptr, &game->img.bpp, &game->img.size_l, &game->img.endian);
}

// 함수 main_loop 무슨 뜻인지 모르겠다.
int		main_loop(t_game *game)
{
	draw_rectangles(game);
	draw_lines(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0); // image 를 의도한 각각의 좌표에 따라 배치
	return (0);
}

int		main(void)
{
	t_game game;

	game_init(&game);
	window_init(&game);
	img_init(&game);
	mlx_hook(game.win, X_EVENT_KEY_PRESS, 0, &deal_key, &game);  // KEY_PRESS 받는 mlx_hook
	mlx_hook(game.win, X_EVENT_KEY_EXIT, 0, &close, &game); // KEY_EXIT 받는 mlx_hook
	// mlx_hook 은 모든 입력을 처리하는 함수 x_event값에 따라
	// key_press, key_release, mouse클릭, 창닫기버튼 등 입력을 받을 수 있음
	mlx_loop_hook(game.mlx, &main_loop, &game);
	// 아무 입력이 없을때 계속 loop를 돌리는 함수. 이 함수를 이용해 현재 위치 정보를 기반으로 화면을 매번 새로 그리면 됩니다.
	mlx_loop(game.mlx);
	// 마지막에 이걸 쳐줘야 프로그램이 종료하지 않고 계속 돌아갑니다.
}
