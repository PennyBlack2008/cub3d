#include "cub_21.h"

// 화살표 오른쪽 방향키 누르면 시계 방향으로 회전
int					rotate_right(t_win *w)
{
	int	x, y;

	double pos_x, pos_y;
	double add_player_x, add_player_y;
	double new_angle;

	new_angle = w->player.ang - 30 * M_PI / 180;
	x = w->player.width / 2 * -1;
	while (x < w->player.width / 2)
	{
		y = w->player.height / 2 * -1;
		while (y < w->player.height / 2)
		{
			pos_x = x * cos(new_angle * -1) + y * sin(new_angle * -1);
			pos_y = x * sin(new_angle * -1) * -1 + y * cos(new_angle * -1);
			add_player_x = pos_x + w->player.x;
			add_player_y = pos_y + w->player.y;
			if (add_player_x >= 0 && add_player_y >= 0)
			{
				if (is_wall(add_player_x, add_player_y, w) == WALL)
					return (WALL);
			}
			y++;
		}
		x++;
	}
	w->player.ang += 30 * M_PI / 180;
	return (NOT_WALL);
}

// 화살표 왼쪽 방향키 누르면 시계 방향으로 회전
int					rotate_left(t_win *w)
{
	int	x, y;

	double pos_x, pos_y;
	double add_player_x, add_player_y;
	double new_angle;

	new_angle = w->player.ang - 30 * M_PI / 180;
	x = w->player.width / 2 * -1;
	while (x < w->player.width / 2)
	{
		y = w->player.height / 2 * -1;
		while (y < w->player.height / 2)
		{
			pos_x = x * cos(new_angle * -1) + y * sin(new_angle * -1);
			pos_y = x * sin(new_angle * -1) * -1 + y * cos(new_angle * -1);
			add_player_x = pos_x + w->player.x;
			add_player_y = pos_y + w->player.y;
			if (add_player_x >= 0 && add_player_y >= 0)
			{
				if (is_wall(add_player_x, add_player_y, w) == WALL)
					return (WALL);
			}
			y++;
		}
		x++;
	}
	w->player.ang -= 30 * M_PI / 180;
	return (NOT_WALL);
}

int					move_forward(t_win *w)
{
	int	x, y;

	double pos_x, pos_y;
	double add_player_x, add_player_y;

	// 돌리는 건 성공했는 데, 애초에 사각형의 끝점을 중심으로 그렸기 때문에 내가 원하는 공식을 쓸 수가 없다.
	x = w->player.width / 2 * -1;
	while (x < w->player.width / 2)
	{
		y = w->player.height / 2 * -1;
		while (y < w->player.height / 2)
		{
			pos_x = x * cos(w->player.ang * -1) + y * sin(w->player.ang * -1);
			pos_y = x * sin(w->player.ang * -1) * -1 + y * cos(w->player.ang * -1);
			add_player_x = pos_x + w->player.x + 10 * cos(w->player.ang * -1);
			add_player_y = pos_y + w->player.y - 10 * sin(w->player.ang * -1);
			if (add_player_x >= 0 && add_player_y >= 0)
			{
				if (is_wall(add_player_x, add_player_y, w) == WALL)
					return (WALL);
			}
			y++;
		}
		x++;
	}
	w->player.x += 10 * cos(w->player.ang * -1);
	w->player.y -= 10 * sin(w->player.ang * -1);
	return (NOT_WALL);
}

int					move_back(t_win *w)
{
	int	x, y; // 그저 인덱스
	double pos_x, pos_y;
	double add_player_x, add_player_y;

	// 돌리는 건 성공했는 데, 애초에 사각형의 끝점을 중심으로 그렸기 때문에 내가 원하는 공식을 쓸 수가 없다.
	x = w->player.width / 2 * -1;
	while (x < w->player.width/2)
	{
		y = w->player.height / 2 * -1;
		while (y < w->player.height/2)
		{
			pos_x = x * cos(w->player.ang) + y * sin(w->player.ang);
			pos_y = x * sin(w->player.ang) * -1 + y * cos(w->player.ang);
			add_player_x = pos_x + w->player.x - 10 * cos(w->player.ang * -1);
			add_player_y = pos_y + w->player.y + 10 * sin(w->player.ang * -1);
			if (add_player_x >= 0 && add_player_y >= 0)
			{
				if (is_wall(add_player_x, add_player_y, w) == WALL)
					return (WALL);
			}
			y++;
		}
		x++;
	}
	w->player.x -= 10 * cos(w->player.ang * -1);
	w->player.y += 10 * sin(w->player.ang * -1);
	return (NOT_WALL);
}

int					move_left(t_win *w)
{
	int	x, y;
	double pos_x, pos_y;
	double add_player_x, add_player_y;

	// 돌리는 건 성공했는 데, 애초에 사각형의 끝점을 중심으로 그렸기 때문에 내가 원하는 공식을 쓸 수가 없다.
	x = w->player.width / 2 * -1;
	while (x < w->player.width / 2)
	{
		y = w->player.height / 2 * -1;
		while (y < w->player.height / 2)
		{
			pos_x = x * cos(w->player.ang * -1) + y * sin(w->player.ang * -1);
			pos_y = x * sin(w->player.ang * -1) * -1 + y * cos(w->player.ang * -1);
			add_player_x = pos_x + w->player.x - 10 * cos(M_PI_2 - (w->player.ang * -1));
			add_player_y = pos_y + w->player.y - 10 * sin(M_PI_2 - (w->player.ang * -1));;
			if (add_player_x >= 0 && add_player_y >= 0)
			{
				if (is_wall(add_player_x, add_player_y, w) == WALL)
					return (WALL);
			}
			y++;
		}
		x++;
	}
	w->player.x -= 10 * cos(M_PI_2 - (w->player.ang * -1));
	w->player.y -= 10 * sin(M_PI_2 - (w->player.ang * -1));
	return (NOT_WALL);
}

int					move_right(t_win *w)
{
	int	x, y;

	double pos_x, pos_y;
	double add_player_x, add_player_y;

	// 돌리는 건 성공했는 데, 애초에 사각형의 끝점을 중심으로 그렸기 때문에 내가 원하는 공식을 쓸 수가 없다.
	x = w->player.width / 2 * -1;
	while (x < w->player.width / 2)
	{
		y = w->player.height / 2 * -1;
		while (y < w->player.height / 2)
		{
			pos_x = x * cos(w->player.ang * -1) + y * sin(w->player.ang * -1);
			pos_y = x * sin(w->player.ang * -1) * -1 + y * cos(w->player.ang * -1);
			add_player_x = pos_x + w->player.x + 10 * cos(M_PI_2 - (w->player.ang * -1));
			add_player_y = pos_y + w->player.y + 10 * sin(M_PI_2 - (w->player.ang * -1));
			if (add_player_x >= 0 && add_player_y >= 0)
			{
				if (is_wall(add_player_x, add_player_y, w) == WALL)
					return (WALL);
			}
			y++;
		}
		x++;
	}
	w->player.x += 10 * cos(M_PI_2 - (w->player.ang * -1));
	w->player.y += 10 * sin(M_PI_2 - (w->player.ang * -1));
	return (NOT_WALL);
}
