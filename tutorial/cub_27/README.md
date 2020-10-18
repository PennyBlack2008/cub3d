광선들이 벽에 부딪히면 멈추도록 cub_26의 코드에서 if 문만 추가하여 만들었습니다.

20201009 추가사항: 함수 mlx_put_image_to_window 를 draw_line 에서 제거하니 속도가 비약적으로 빨라졌습니다.
20201018 추가사항: 벽의 너비와 플레이어의 가로 세로 길이를 유연하게 설정할 수 있도록 했습니다.(tile length 가 바뀌어도 100 이하의 길이는 출력함)

밑의 사진은 코드 업데이트 전이라 결과물과 상이함

![ray_casting_basic_2](https://user-images.githubusercontent.com/59194905/94107582-c56ce480-fe78-11ea-9c51-ab056503aed7.gif)

map.c 의 픽셀이 벽에 해당되는 지 판단해주는 int is_wall(double x, double y, t_win *w) 함수를 사용하였습니다.

test2.c 에 있는 함수 draw_ray 코드입니다.
```
int					draw_ray(t_win *w, double ang)
{
	int x, y;
	double pos_x, pos_y;
	double add_player_x, add_player_y;

	x = 0;
	while (x < WIN_WIDTH / 2)
	{
		y = 0;
		pos_x = x * cos((w->player.ang + ang) * -1) + y * sin((w->player.ang + ang) * -1);
		pos_y = x * sin((w->player.ang + ang) * -1) * -1 + y * cos((w->player.ang + ang) * -1);
		add_player_x = pos_x + w->player.x;
		add_player_y = pos_y + w->player.y;
		if (add_player_x >= 0 && add_player_y >= 0)
		{
			my_mlx_pixel_put(&w->img, add_player_x, add_player_y, 0xFF0000);
			if (is_wall(add_player_x, add_player_y, w) == WALL) // <----- 여기가 중요!
				break ;
		}
		x++;
	}
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr, 0, 0);
	return (0);
}
```

주의할 점은 함수 is_wall 는 move.c 파일에서 이미 많이 사용되고 있으니 변형할 때는 move.c 파일에 있는 함수들도 같이 고려해서 바꾸어야합니다.