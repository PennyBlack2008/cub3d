cub 18

i will convert 1 dimension data(char *map) into 2 dimension data(char **map)

it will make it possible that we can handle map data very comfortable

## 상세 학습 내용
> get_next_line 으로 ``*.cub`` 의 정보 받아서 구조체 멤버들에 저장하기

1차원 배열의 맵을 2차원으로 만드는 코드를 짰는 데, 잘못된 작동이어서 계속 디버깅 했습니다. 제가 보기에 틀린 것이 없다고 생각했고 테스트 결과가 어떤 것이 잘 못되었는 지 알기가 힘들었습니다. 문제가 쉽게 풀릴 거라 생각해서 머리로 풀려고 했다가 실패하기를 반복해서 정신이 피폐해졌습니다. 오늘 이 코드만 생각해도 피곤했고 오랜만에 걷는 운동을 했는 데도 버거울 만큼 피폐해졌습니다.

결국 5시간 만에 코드를 완성했습니다. 어떤 문제였냐면 flag가 있는 1차원 배열을 2차원 맵으로 만들 때 생기는 문제였습니다. 예를 들어 flag 가 있을 때마다 첫번째 세로부분의 인덱스를 늘려주는 2차원 맵이라면, 가로인덱스가 0일 때 flag 를 만나면 세로로 증가를 시켜준다면 한 줄 한 줄 이빨빠진 호랑이 처럼 데이터가 삽입이 됩니다.

백지상태에서 시도해보면 생각하기 정말 어려운 코드이고 이해하기 어렵습니다.

```
// 2. char **map 에 char *map 집어 넣기
	i = 0;		j = 0;		k = 0;
	while (i < m->map_height && (m->map_1d[k] != '\0'))
	{
		j = 0;
		while (j < m->map_width && (m->map_1d[k] != '\0'))
		{
			if ((m->map_1d[k] == '\n') && (j == 0)) // <---------- 정말 어려웠던 예외처리!!
				m->map[i][j] = m->map_1d[++k];
			else if (m->map_1d[k] == '\n')
			{
				j = INT_MAX;
				k++;
			}
			else
				m->map[i][j++] = m->map_1d[k++];
		}
		i++;
	}
```