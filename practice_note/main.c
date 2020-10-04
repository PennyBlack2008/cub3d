/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:45:06 by ncolomer          #+#    #+#             */
/*   Updated: 2020/08/12 20:10:02 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d.h"

/* engine의 engine.h에 있다.
typedef	struct	s_game
{
	t_config	config;
	t_window	window;
	t_camera	camera;
	t_sprite	*sprites;
	t_tex		tex[TEXTURES];
	t_pos		move;
	t_pos		x_move;
	t_pos		rotate;
	int			options;
	int			to_collect;
	int			collected;
	double		camera_x[1920];
	double		depth[1920];
	double		sf_dist[1080];
	double		cos[2];
	double		sin[2];
}				t_game;
*/

// error 처리, 그런데 어디에 에러를 write 하는지 모르겟다. 일단 에러처리는 이 함수에서 다~ 한다. exit_game 라는 함수에서 게임을 끝내는 것 처럼 보인다.
int
	exit_error(t_game *game, char const *str)
{
	if (str)
		write(STDOUT_FILENO, str, ft_strlen(str));
	exit_game(game, EXIT_FAILURE);
	return (EXIT_FAILURE);
}

// main 문, game 이라는 변수가 있는 데 뭐하는 변수인지 모르겠다.
// save_opt	라는 변수는 뭐하는 변수 일까?
int main(int argc, char **argv)
{
	t_game	game;
	int		save_opt;

	save_opt = (argc >= 2 && !ft_strcmp(argv[1], "-save")); // argc 가 2개 이상이고 -save 가 표시된 경우에 save_opt는 1이 된다.
	// 이 줄의 의미는 -save 옵션을 넣어 argc가 증가하면, 맵이 들어와서 argc 가 증가한 거으로 착각하기 때문에 넣은 것이다.
	if (argc < (2 + save_opt)) // map 이 없을 때 발동. 나는 argc가 2 일 때만 발동하는 줄 알았다. save_opt 를 정의하는 줄을 보면 알 수 있다.
		return (exit_error(&game, "Error:\nno map specified.\n"));
	init_game(&game, save_opt); // init_game은 시작하는 것인가?
	// 여기서 아마 game 이라는 구조체에 mlx_init(game.window.ptr) 를 넣어줄 것이다.
	// 그렇다면 init_game 는 어떤 파일에 정의가 되어 있고 mlx_init 말고도 어떤 역할을 해줄 까?
	if (!parse_config(&game.config, argv[1 + save_opt])) // parse_config는 뭐하는 것인가? game.config는 무엇을 뜻하는 것일까?
	// argv[1 + save_opt]는 무슨 의미인가? 아, 이건 map을 넣을 때 --save를 먼저 넣고 map을 써주기 때문에 map은 argv[1 + save_opt]에 있다고 판단한 거구나.
	// game.config는 무슨 의미인지 모르겠다. game이라는 구조체에 config가 달려있구나, parse_config의 if 문을 통해서 invalid map 에러를 도출하는 것 보니깐,
	// parse_config는 map 과 관련한 함수이구나, error나면 무조건 parse_config는 0을 반환하겠지.
	// map 으로 부터 config 설정들을 얻어 game.config 구조체에 넣는다.
		return (exit_error(&game, "Error:\ninvalid map.\n"));
	if (!finish_init(&game)) // finish_init 이라는 함수는 함수의 이름으로 생각해봤을 때, initiation을 끝낸다는 것 같은 데.
	// 로딩이 끝났다 ~ 이정도의 뜻일까?
		return (EXIT_FAILURE);
	if (game.options & FLAG_SAVE) // game의 옵션?
		return (screenshot(&game));
	mlx_hook(game.window.win, X_EVENT_KEY_PRESS, 0, &key_press, &game);
	// mlx가 무엇일까? 내가 그 봤던 그거인가? 음... 어디서 많이 봤는 데,... 함수를 까보자
	// 일단 이 함수는 mlx/interface.swift 에 정의되어 있다.
	// mlx/mlx.h 에 정의되어 있으니 보면 될 것같다.
	// mlx_hook 은 함수를 포인터로 받아 X_event 에 따른 key 입력을 받을 수 있다.
	mlx_hook(game.window.win, X_EVENT_KEY_RELEASE, 0, &key_release, &game);
	mlx_hook(game.window.win, X_EVENT_EXIT, 0, &exit_hook, &game);
	// mlx_hook 은 win 포인터를 받고 mlx_loop 관련 함수들은 mlx 포인터를 받는다.
	mlx_loop_hook(game.window.ptr, &main_loop, &game);
	mlx_loop(game.window.ptr);
	return (EXIT_SUCCESS);
}
