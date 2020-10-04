/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:51:45 by ncolomer          #+#    #+#             */
/*   Updated: 2020/08/12 20:04:37 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

// 아직 밝혀내지 못한 구성 요소, 1. save_arg 2. fov
void
	init_config(t_config *config)
{
	int	i;

	config->requested_width = 848; // 이걸 왜 굳이 848 로 했을 까?
	config->requested_height = 480; // 이걸 왜 굳이 480 로 했을 까?
	i = 0;
	while (i < TEXTURES) // tex_path 초기화 반복문
		config->tex_path[i++] = NULL;
	// config->c[] 인 이유는 color 의 배열이라서 그런 것 같다.
	config->c[TEX_NORTH] = 0xFFFFFF;	//  북 쪽 텍스쳐 색: white, 16777215
	config->c[TEX_SOUTH] = 0xCCCCCC;	//  남 쪽 텍스쳐 색: gray, 13421772
	config->c[TEX_WEST] = 0xFF44FF;		//  서 쪽 텍스쳐 색: pink, 16729343
	config->c[TEX_EAST] = 0x44FF44;		//  동 쪽 텍스쳐 색: green, 4521796
	config->c[TEX_SKY] = 0x33C6E3;		// 천장 쪽 텍스쳐 색: sky blue, 3393251
	config->c[TEX_FLOOR] = 0xA0764C;	// 바닥 쪽 텍스쳐 색: brown, 10516044
	config->map = NULL; // map 은 초기화
	config->rows = 0; // 이 row 가 맵에 해당되는 거 겠지?
	config->columns = 0;
	config->save_arg = 0; // save_arg 는 save_option 과 작용하는 요소일 까?
	config->rotate_speed = .11; // 시점 감도 조절 하는 것 인듯
	config->move_speed = .11; // 움직이는 속도 감도 조절 하는 것 인듯
	config->fov = .66; // fov 의 값은 왜 굳이 .66 일 까? fov 가 의미하는 건 무엇일 까?
	i = 0;
	while (i < C_LAST) // C_LAST 는 무엇일 까?
		config->set[i++] = 0;
}

int
	clear_config(t_config *config)
{
	int	i;

	i = 0;
	while (i < TEXTURES)
	{
		if (config->tex_path[i])
			free(config->tex_path[i]);
		config->tex_path[i] = NULL;
		i++;
	}
	if (config->map)
		free(config->map);
	config->map = NULL;
	return (0);
}

static int
	config_key(char const *line)
{
	if (line[0] == 'R' && line[1] == ' ')
		return (C_R);
	else if (line[0] == 'N' && line[1] == 'O')
		return (C_NO);
	else if (line[0] == 'S' && line[1] == 'O')
		return (C_SO);
	else if (line[0] == 'W' && line[1] == 'E')
		return (C_WE);
	else if (line[0] == 'E' && line[1] == 'A')
		return (C_EA);
	else if (line[0] == 'S' && line[1] == 'T')
		return (C_ST);
	else if (line[0] == 'F' && line[1] == 'T')
		return (C_FT);
	else if (line[0] == 'S' && line[1] == ' ')
		return (C_S);
	else if (line[0] == 'S' && line[1] == 'U')
		return (C_SU);
	else if (line[0] == 'S' && line[1] == 'C')
		return (C_SC);
	else if (line[0] == 'F' && line[1] == ' ')
		return (C_F);
	else if (line[0] == 'C' && line[1] == ' ')
		return (C_C);
	return (C_MAP);
}

int
	parse_line(t_config *config, char const *line, t_str **map_buffer)
{
	static int	empty_in_map = 0;
	static int	content_after = 0;
	int			length;
	int			key;

	length = ft_strlen(line);
	if (length == 0 && config->set[C_MAP])
		empty_in_map = 1;
	if (empty_in_map && content_after)
		return (0);
	if (length == 0)
		return (1);
	key = config_key(line);
	if (key != C_MAP && (config->set[key] || config->set[C_MAP]))
		return (0);
	if (key == C_R)
		return (parse_dimensions(config, line));
	else if (key >= C_NO && key <= C_ST)
		return (parse_texture(config, key, line));
	else if (key == C_F || key == C_C)
		return (parse_color(config, key, line));
	config->set[key] = 1;
	if (empty_in_map)
		content_after = 1;
	return (!!str_add_back(map_buffer, ft_strdup(line)));
}

// file 을 열어 config 를 받아온다. conf_path 는 map 을 의미한다.
// map_buffer 로 map 으로부터 하나하나씩 받아온다.
int
	parse_config(t_config *config, char const *conf_path)
{
	int			c_fd;
	char		*line;
	int			r;
	t_str		*map_buffer;

	if (!ft_endwith(conf_path, ".cub"))
		return (0);
	if ((c_fd = open(conf_path, O_RDONLY)) < 0)
		return (0);
	map_buffer = NULL;
	r = 1;
	while (get_next_line(c_fd, &line))
	{
		r = (r && parse_line(config, line, &map_buffer));
		free(line);
	}
	if (r && ft_strlen(line) > 0)
		r = !!str_add_back(&map_buffer, ft_strdup(line));
	free(line);
	close(c_fd);
	if (!r || !parse_map(config, map_buffer))
		return (str_clear(&map_buffer));
	str_clear(&map_buffer);
	return (1);
}
