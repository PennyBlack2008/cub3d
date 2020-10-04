// 출처: https://github.com/taelee42/mlx_example

// gcc -I ../minilibx -L ../minilibx -lmlx -framework Appkit -framework OpenGL main.c
#include "../minilibx/mlx.h"

int main(void)
{
	void *mlx; // mlx 포인터란?
	void *win; // win 포인터란?

	mlx = mlx_init(); // mlx 란 것을 실행시킨다.
	win = mlx_new_window(mlx, 1000, 500, "mlx_project"); // mlx를 첫번째 인자로 받고 나머지는 해상도와 이름을 출력한다. 가로, 세로 순
	mlx_loop(mlx);
}

/* 이 함수에서는 exit을 눌러도 나가지지 않고 ctrl+C를 입력해야 겨우 나가진다. 그리고 Ctrl+C를 누르지 않고 창을 끄면 터미널에서 main문이 종료되지 않고 계속 돌아간다.

void	*mlx_init();
설명: needed before everything else. -return (void *)0 if failed


void	*mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title);


mlx_loop(mlx); 에 관한 설명은 md 파일에 있다.
설명: To receive events, you must use mlx_loop (). This function never returns. It is an infinite
       loop  that  waits for an event, and then calls a user-defined function associated with this
       event.  A single parameter is needed, the connection identifier mlx_ptr (see the  mlx  man-
       ual). 대충 마우스 클릭, 키보드 클릭 같은 Input을 받으려면 이 함수가 계속 loop를 통해 계속 돌면서 프로그램이 종료되지 않도록 해준다는 뜻인듯.
*/
