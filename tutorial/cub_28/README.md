cub_28 : 레이케스팅 광선 만들기. 이전의 것 보다 더 효율적인 코드입니다.

https://permadi.com/1996/05/ray-casting-tutorial-7/

링크의 이론 대로 코드를 작성하는 것인데, 너무 많이 실패하고 시간을 소비해서

이 폴더에서 이 영역에 해당되는 것만 일단 최대한 간단히 해보려고 합니다.

광선을 여러군데로 뿌려서 광선이 벽에 부딛히는 지 검사를 하는 예전 코드와 다르게 

벽에 부딛히는 점만 간단한 기하학적인 계산을 통해 계산합니다.

코드의 결과

<img width="1002" alt="스크린샷 2020-10-03 오후 5 05 56" src="https://user-images.githubusercontent.com/59194905/94986587-ef21bc00-059a-11eb-842a-04daf1b7031a.png">

여기서 힘들었던 점은

함수 is_wall_ray 의 필요성을 몰랐기 때문입니다. 이 글을 이해하기 전에 TILE의 경계선에 걸치는 점을 계산하는 방법(https://permadi.com/1996/05/ray-casting-tutorial-7/)을 이해해야합니다.

잘못된 생각: 광선이 벽에 부딛히는 점을 계산할 수 있는데, 그 점이 벽에 해당되는 경계선이냐, 벽에 해당되지 않는 경계선이냐가 중요하다고 생각했었습니다.

올바른 생각: 벽에 걸쳐있는 경계선은 벽이 될 때도 있고 벽이 아닐 때도 있습니다. 중요한 것은 광선이 비어있는 공간에서 출발하여 벽을 만났느냐? 입니다. 

광선의 발원지도 함께 고려하여 이것이 벽이냐 아니냐를 판단해야합니다. 그래서 저는 벽에 부딛히는 점을 계산한 좌표에 광선의 방향에 따라 광선이 뚫고 나가는 바로 그 다음 좌표를 함수 is_wall 이라는 것에 넣어 벽인지 판단했습니다.

함수: is_wall
```
int			is_wall(double x, double y, t_win *w)
{
	if (w->map.map[(int)(y / TILE_LENGTH)][(int)(x / TILE_LENGTH)] == WALL)
		return (WALL);
	// printf("w->map.map[%d][%d] = %d\n", (int)(y / TILE_WIDTH), (int)(x / TILE_HEIGHT), w->map.map[(int)(y / TILE_HEIGHT)][(int)(x / TILE_WIDTH)]);
	return (NOT_WALL);
}
```

함수: is_wall_ray
```
int			is_wall_ray(double x, double y, t_ray *r, t_win *w)
{
		if (0 == r->ang)
		{
			return(is_wall(x + 1, y, w));
		}
		else if (0 < r->ang && r->ang < M_PI_2)
		{
			printf("제 1사분면\n");
			return(is_wall(x + 1, y + 1, w));
		}
		else if (M_PI_2 == r->ang)
		{
			return(is_wall(x , y + 1, w));
		}
		else if (M_PI_2 < r->ang && r->ang < M_PI)
		{
			printf("제 2사분면\n");
			return(is_wall(x - 1, y + 1, w));
		}
		else if (M_PI == r->ang)
		{
			return(is_wall(x - 1, y, w));
		}
		else if (M_PI < r->ang && r->ang < M_PI_2 * 3)
		{
			printf("제 3사분면\n");
			return(is_wall(x - 1, y - 1, w));
		}
		else if (M_PI_2 * 3 == r->ang)
		{
			return(is_wall(x, y - 1, w));
		}
		else if (M_PI_2 * 3 < r->ang && r->ang < 2 * M_PI)
		{
			printf("제 4사분면\n");
			return(is_wall(x + 1, y - 1, w));
		}
		
	return (0);
}
```