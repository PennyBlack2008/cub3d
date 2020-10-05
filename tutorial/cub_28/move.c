#include "cub_28.h"

#define NINETY_DEGREE 90 * M_PI / 180
#define WALL 49
#define NOT_WALL 48

// 화살표 오른쪽 방향키 누르면 시계 방향으로 회전
int					rotate_right(t_win *w)
{
	w->player.ang += 30 * M_PI / 180;
	return (NOT_WALL);
}

// 화살표 왼쪽 방향키 누르면 시계 방향으로 회전
int					rotate_left(t_win *w)
{
	w->player.ang -= 30 * M_PI / 180;
	return (NOT_WALL);
}


int					move_forward(t_win *w)
{
	w->player.x += 10 * cos(w->player.ang * -1);
	w->player.y -= 10 * sin(w->player.ang * -1);
	return (NOT_WALL);
}

int					move_back(t_win *w)
{
	w->player.x -= 10 * cos(w->player.ang * -1);
	w->player.y += 10 * sin(w->player.ang * -1);
	return (NOT_WALL);
}

int					move_left(t_win *w)
{
	w->player.x -= 10 * cos(M_PI_2 - (w->player.ang * -1));
	w->player.y -= 10 * sin(M_PI_2 - (w->player.ang * -1));
	return (NOT_WALL);
}

int					move_right(t_win *w)
{
	w->player.x += 10 * cos(M_PI_2 - (w->player.ang * -1));
	w->player.y += 10 * sin(M_PI_2 - (w->player.ang * -1));
	return (NOT_WALL);
}
