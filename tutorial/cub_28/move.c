#include "cub_21.h"

// 화살표 오른쪽 방향키 누르면 시계 방향으로 회전
int					rotate_right(t_win *w)
{
	int	x, y;
	t_plot	plot;
	t_plot	plot_player;
	double new_angle;

	new_angle = w->player.ang - 30 * M_PI / 180;
	x = w->player.width / 2 * -1;
	while (x < w->player.width / 2)
	{
		y = w->player.width / 2 * -1;
		while (y < w->player.width / 2)
		{
			plot.x = x * cos(new_angle * -1) + y * sin(new_angle * -1);
			plot.y = x * sin(new_angle * -1) * -1 + y * cos(new_angle * -1);
			plot_player.x = plot.x + w->player.x;
			plot_player.y = plot.y + w->player.y;
			if (plot_player.x >= 0 && plot_player.y >= 0)
			{
				if (is_wall(plot_player.x, plot_player.y, w) == WALL)
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
	t_plot	plot;
	t_plot	plot_player;
	double new_angle;

	new_angle = w->player.ang - 30 * M_PI / 180;
	x = w->player.width / 2 * -1;
	while (x < w->player.width / 2)
	{
		y = w->player.width / 2 * -1;
		while (y < w->player.width / 2)
		{
			plot.x = x * cos(new_angle * -1) + y * sin(new_angle * -1);
			plot.y = x * sin(new_angle * -1) * -1 + y * cos(new_angle * -1);
			plot_player.x = plot.x + w->player.x;
			plot_player.y = plot.y + w->player.y;
			if (plot_player.x >= 0 && plot_player.y >= 0)
			{
				if (is_wall(plot_player.x, plot_player.y, w) == WALL)
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
	t_plot	plot;
	t_plot	plot_player;
	
	// 돌리는 건 성공했는 데, 애초에 사각형의 끝점을 중심으로 그렸기 때문에 내가 원하는 공식을 쓸 수가 없다.
	x = w->player.width / 2 * -1;
	while (x < w->player.width / 2)
	{
		y = w->player.width / 2 * -1;
		while (y < w->player.width / 2)
		{
			plot.x = x * cos(w->player.ang * -1) + y * sin(w->player.ang * -1);
			plot.y = x * sin(w->player.ang * -1) * -1 + y * cos(w->player.ang * -1);
			plot_player.x = plot.x + w->player.x + 10 * cos(w->player.ang * -1);
			plot_player.y = plot.y + w->player.y - 10 * sin(w->player.ang * -1);
			if (plot_player.x >= 0 && plot_player.y >= 0)
			{
				if (is_wall(plot_player.x, plot_player.y, w) == WALL)
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
	int	x, y;
	t_plot	plot;
	t_plot	plot_player;

	// 돌리는 건 성공했는 데, 애초에 사각형의 끝점을 중심으로 그렸기 때문에 내가 원하는 공식을 쓸 수가 없다.
	x = w->player.width / 2 * -1;
	while (x < w->player.width / 2)
	{
		y = w->player.width / 2 * -1;
		while (y < w->player.width / 2)
		{
			plot.x = x * cos(w->player.ang) + y * sin(w->player.ang);
			plot.y = x * sin(w->player.ang) * -1 + y * cos(w->player.ang);
			plot_player.x = plot.x + w->player.x - 10 * cos(w->player.ang * -1);
			plot_player.y = plot.y + w->player.y + 10 * sin(w->player.ang * -1);
			if (plot_player.x >= 0 && plot_player.y >= 0)
			{
				if (is_wall(plot_player.x, plot_player.y, w) == WALL)
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
	t_plot	plot;
	t_plot	plot_player;

	// 돌리는 건 성공했는 데, 애초에 사각형의 끝점을 중심으로 그렸기 때문에 내가 원하는 공식을 쓸 수가 없다.
	x = w->player.width / 2 * -1;
	while (x < w->player.width / 2)
	{
		y = w->player.width / 2 * -1;
		while (y < w->player.width / 2)
		{
			plot.x = x * cos(w->player.ang * -1) + y * sin(w->player.ang * -1);
			plot.y = x * sin(w->player.ang * -1) * -1 + y * cos(w->player.ang * -1);
			plot_player.x = plot.x + w->player.x - 10 * cos(M_PI_2 - (w->player.ang * -1));
			plot_player.y = plot.y + w->player.y - 10 * sin(M_PI_2 - (w->player.ang * -1));;
			if (plot_player.x >= 0 && plot_player.y >= 0)
			{
				if (is_wall(plot_player.x, plot_player.y, w) == WALL)
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
	t_plot	plot;
	t_plot	plot_player;

	// 돌리는 건 성공했는 데, 애초에 사각형의 끝점을 중심으로 그렸기 때문에 내가 원하는 공식을 쓸 수가 없다.
	x = w->player.width / 2 * -1;
	while (x < w->player.width / 2)
	{
		y = w->player.width / 2 * -1;
		while (y < w->player.width / 2)
		{
			plot.x = x * cos(w->player.ang * -1) + y * sin(w->player.ang * -1);
			plot.y = x * sin(w->player.ang * -1) * -1 + y * cos(w->player.ang * -1);
			plot_player.x = plot.x + w->player.x + 10 * cos(M_PI_2 - (w->player.ang * -1));
			plot_player.y = plot.y + w->player.y + 10 * sin(M_PI_2 - (w->player.ang * -1));
			if (plot_player.x >= 0 && plot_player.y >= 0)
			{
				if (is_wall(plot_player.x, plot_player.y, w) == WALL)
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
