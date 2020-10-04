/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 12:51:35 by ncolomer          #+#    #+#             */
/*   Updated: 2020/08/12 19:59:41 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// 반짝 반짝 빛나는 물체 말하는 듯.
static int
	find_sprites(t_game *game)
{
	int		i;
	int		j;
	t_pos	pos;
	char	c;
	t_tex	*tex;

	game->sprites = NULL;
	i = 0;
	while (i < game->config.rows)
	{
		j = 0;
		while (j < game->config.columns)
		{
			set_pos(&pos, j + .5, i + .5);
			c = MAP(pos, game->config);
			tex = &game->tex[TEX_SPRITE + (c - '0' - 2)];
			if (c >= '2' && c <= '4' && tex->tex
				&& !add_front_sprite(&game->sprites, 0., &pos, tex))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int
	exit_game(t_game *game, int code)
{
	clear_config(&game->config);
	clear_window(&game->window);
	clear_textures(game);
	clear_sprites(&game->sprites);
	exit(code);
	return (code);
}

// main.c 에서 쓰인 함수. 게임을 시작하기 위해 mlx, win 포인터의 아이덴티티를 정해준다.
// 생각보다 많은 역할을 해서 놀랍다. 함수 mlx_init 말고 몇가지 없을 줄 알았는 데
// 플레이어의 초기 위치와 관련한 변수(x, y, rotate)를 정해준다.
void
	init_game(t_game *game, int save_opt)
{
	int	i;

	init_config(&game->config); // 여기에 아마 mlx_init 이 있을 텐데, init_config 를 열어봐야 겠다.
	// 이 함수는 어디에 정의되어 있을 까? config/config.c
	// 벽 색, 무빙 속도, 카메라 감도 설정
	set_pos(&game->move, 0, 0);
	set_pos(&game->x_move, 0, 0);
	set_pos(&game->rotate, 0, 0);
	game->collected = 0; // game 구조체의 collected 는 별을 먹었을 때 점수를 얻는 개념의 역할을 하는 것
	// 으로 보인다.
	game->options = 0x11111110; // 이 역할은 정말 모르겠다. 옵션? 그리고 이 숫자는 286331152 이다.
	game->sprites = NULL; // 이거는 민창님이 요정 같은 거라고 했고, 구글에는 2D 표현 방식이라고 해야되나? 이해못했지만
	// 그냥 맵의 구석구석에 있는 애니메이션 표현? 그런거 같다.
	if (save_opt) // save_opt 가 있으면 1 이다. 그래서 if 문이 돌아간다.
		game->options = game->options | FLAG_SAVE;
	i = 0;
	while (i < TEXTURES) // TEXTURES 와 관련된 구조체 game의 멤버인 game->tex[].tex 도 초기화가 필요함
		game->tex[i++].tex = NULL;
	// 단순히 game 을 사용할 때 포인터로 선언하기 때문에 그런 것이라고 이해는 가능하다.
}

// 게임을 시작하기 전에 init_game 을 하는 것은 이해하겠는 데, 왜 finish_init 이 굳이 필요할 까?
int
	finish_init(t_game *game)
{
	if (!init_window(&game->window, &game->config))
	{
		return (exit_error(game,
			"Error:\nmlx failed to create window or image.\n"));
	}
	find_start_pos(&game->config, &game->camera);
	find_start_angle(&game->config, &game->camera);
	if (!load_textures(game))
		return (exit_error(game, "Error:\nfailed to load texture(s).\n"));
	if (!find_sprites(game))
		return (exit_error(game, "Error:\nfailed to malloc sprites.\n"));
	count_items(game);
	make_tables(game);
	return (1);
}

int
	screenshot(t_game *game)
{
	update_screen(game);
	update_ui(game);
	update_window(game);
	if (!save_bmp(game))
		exit_error(game, "Error:\nfailed to save screenshot.");
	return (exit_game(game, EXIT_SUCCESS));
}
