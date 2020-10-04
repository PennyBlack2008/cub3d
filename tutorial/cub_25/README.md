cub_25

It shows a map relative to char **map.

TILE_SIZE is automatically defined through defining ROWS, COLS, WIN_WIDTH, WIN_HEIGHT

Those code is in map.c

cub_24 에서 고친 기능!: 이제 회전을 해도 플레이어의 정면 화살표에 따라 플레이어가 움직일 수 있습니다.

해결 방법: 처음에 각도가 0일 때, x축으로 플레이어가 움직이는 거리가 있다면 플레이어가 회전하여 각도가 변화할 때, 각각 x, y 축 방향으로 거리가 어떻게 증가 또는 감소 되는 지 생각해야합니다.

플레이어가 움직이는 거리는 무조건 일정하고 각도만 변하기 때문에 이등변삼각형을 생각합니다. 그리고 그 다음에 직각이 되는 직각삼각형을 찾아 삼각함수를 이용하여 각도에 따라 각각 x, y 축에 따라 어떻게 변화하는 지 계산하면 됩니다.