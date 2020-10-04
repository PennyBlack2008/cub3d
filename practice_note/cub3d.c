/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:44:32 by ncolomer          #+#    #+#             */
/*   Updated: 2020/08/12 18:54:29 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// 이 파일에는 key input 를 받아 조작되고 그에 해당되는 action 을 설정해 줄 수 있다.
int
	exit_hook(t_game *game)
{
	return (exit_game(game, EXIT_SUCCESS));
}

// key 가 눌리면 move.x 에 1을 삽입하는 데, 이것은 x 축으로 1 만큼 움직여라 가 아닌 0 이면 입력을 받지 않았다.
// 1 이면 입력을 받았다. ~라는 뜻인 것 같다.
int
	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_FORWARD)
		game->move.x = 1;
	else if (keycode == KEY_S || keycode == KEY_BACKWARD)
		game->move.y = 1;
	if (keycode == KEY_A)
		game->x_move.x = 1;
	else if (keycode == KEY_D)
		game->x_move.y = 1;
	if (keycode == KEY_Q || keycode == KEY_LEFT)
		game->rotate.x = 1;
	else if (keycode == KEY_E || keycode == KEY_RIGHT)
		game->rotate.y = 1;
	return (0);
}

// key_release 는 왜 필요할 까? 내가 보기에는 0으로 초기화 하는 것 같다.
int
	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_FORWARD)
		game->move.x = 0;
	else if (keycode == KEY_S || keycode == KEY_BACKWARD)
		game->move.y = 0;
	else if (keycode == KEY_A)
		game->x_move.x = 0;
	else if (keycode == KEY_D)
		game->x_move.y = 0;
	else if (keycode == KEY_Q || keycode == KEY_LEFT)
		game->rotate.x = 0;
	else if (keycode == KEY_E || keycode == KEY_RIGHT)
		game->rotate.y = 0;
	else if (keycode == KEY_ESC)
		return (exit_game(game, EXIT_SUCCESS));
	// 이 부분에서 FLAG_UI, FLAG_SHADOWS, FLAG_CROSSHAIR 중 한 가지를 세팅할 수 있는 것 같다.
	else if (keycode == KEY_I)
		game->options = game->options ^ FLAG_UI; // HUI 말하는 듯.
	else if (keycode == KEY_L)
		game->options = game->options ^ FLAG_SHADOWS; // 그림자는 왜 필요할 까?
	else if (keycode == KEY_O)
		game->options = game->options ^ FLAG_CROSSHAIR; // FPS 십자선을 말하는 데,
		// 이 프로그램에 십자가가 있었던 가?
	return (0);
}

// main_loop 에는 시점과 관련한 함수들이 들어 있다. 움직일 때마다
// update 를 해주어야 움직이는 것처럼 보이기 때문이다.
int
	main_loop(t_game *game)
{
	static int	update = 1;
	static int	last_opt = 0x00000111; // 273

	if (game->move.x || game->move.y)
		update = move_camera(game, (game->move.x) ? 0 : 1);
	if (game->x_move.x || game->x_move.y) // 그냥 move 는 알겠는 데, x_move 는 무엇을 뜻하는 것일까?
		update = move_perp_camera(game, (game->x_move.x) ? 0 : 1); // perp camera 는 감시 카메라를 의미 하는 것같다.
	if (game->rotate.x || game->rotate.y)
		update = rotate_camera(game, (game->rotate.x) ? 0 : 1);
	if (last_opt != game->options) // move_camera, perp_camera, rotate_camera 중 한 가지가 이 게임에 카메라
	// 옵션으로 쓰이는 것 같아 보인다.
	{
		update = 1;
		last_opt = game->options;
	}
	if (update) // update 라는 변수는 key 로 부터 입력을 받아 움직이게 되면 카메라가 update를 하게 되는 데 그것을 의미하는 것 같아보인다.
	{
		if (game->to_collect > 0)
			check_quest(game); // check_quest 는 어디에 정의되어 있을 까?
		MAP(game->camera.pos, game->config) = 'A';
		update_screen(game);
		update_window(game);
	}
	update = 0;
	return (0);
}
