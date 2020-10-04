// 출처: https://github.com/taelee42/mlx_example
// gcc -I ../minilibx -L ../minilibx -lmlx -framework Appkit -framework OpenGL main.c

// 이 코드의 결과는 윈도우(넓이 800, 높이 600)의 까만 창에 이미지(넓이 400, 높이 300)가 들어간다.
// 이 이미지를 main문의 while문을 통해 색을 입히는 것이다.

#include "../minilibx/mlx.h"
#include <stdio.h>

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

# define IMG_WIDTH 400
# define IMG_HEIGHT 300

typedef struct	s_img
{
	void		*img_ptr; // 함수 mlx_new_image 를 통해서 값이 정해진다. 말 그대로 이미지를 가르키는 포인터인 것같다.
	// 아마 내 생각으로는 함수 mlx_new_image 가 계산할 때마다 각각의 img_ptr마다 다른 이미지 포인터 값을 배정할 것같다.
	int			*data;
	//You don't need to understand the 3 values below.
	//After declaration, it will be automatically initialized when passed to mlx_get_data_addr function.
	//아래 3개 값은 이해 안해도 사용하는데 지장이 없음.
	//선언한뒤 함수의 인자로만 잘 넣어주면 알아서 정보를 받아나옴.
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct	s_mlx
{
	void		*mlx_ptr; // 흔히 쓰이는 minilx를 사용하기 위한 mlx 포인터
	void		*win; // 표기하고자 하는 window 의 identity를 위한 win 포인터
}				t_mlx;

int	main(void)
{
	t_mlx	*mlx;
	int		count_w; // count_w 와 count_h 가 뭘까?
	int		count_h;
	t_img	img;

	mlx->mlx_ptr = mlx_init();// 동적할당을 내부적으로 해주어서 mlx->를 쓰는 듯하다.
	mlx->win = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "A simple example");
	img.img_ptr = mlx_new_image(mlx->mlx_ptr, IMG_WIDTH, IMG_HEIGHT);
	// img.img_ptr 는 무엇일까? 어떤 의미이고 어떤 역할을 할 까?
	// 이 함수로 받아온 img.img_ptr은 mlx_get_data_addr로 들어가 계산을 거쳐 img.data에 들어갈 값을 정해준다.
	img.data = (int *)mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l, &img.endian);
	// 이 img.data에 값을 while문으로 배정해주기 전에 함수 mlx_get_data_addr로 초기화같은 것을 해주는 것같다.
	// mlx_get_data_addr은 데이터 주소를 갖게 해준다? 라고 이름을 지은 것같다.
	// 이 함수의 파라미터인 img.bpp, img.size_l, img.endian의 의미를 알아야 할 것같다.
	// 일단 &로 받은 파라미터가 mlx_get_data_addr 함수를 통해서 어떠한 값을 받아오는 건 확실하다.
	// 함수 mlx_get_data_addr의 결과값을 왜 int * 로 캐스팅했을까?
	// 배열의 values 를 참고하려면 곱하기 4를 해야한다? 이게 무슨 말일까?
	//Check out keuhdall's github linked in my README for more information.

	//여기서 (int *)를 안해주고 img.data가 void *이면 밑에 배열값들을 0참조할 때 다 4를 곱해야한다.
	//그렇기 때문에 int *로 캐스팅해주는편이 좋다고 한다.
	// 원래는 배열값을 참조할 때 4를 곱해야하는 데, 이것을 대체해서 (int *)를 캐스팅해주는 것이다.
	//keuhdall's github가면 더 자세한 내용을 볼 수 있습니다.
	/* keuhdall's github
	 Now the important part :
	 mlx_get_data_addr will return a char* that is 4 times the (width * height) of your image.
	 Why so ? Let me explain : This char* will represent your image, pixel by pixel,
	 and the values of this array are the colors. That's why the array is 4 times bigger :
	 you need 4 char to code the color of each pixels (one for Red, Green and Blue) and one for the alpha.
	 But... it's not very convenient, right ? So here is my little trick : you cast
	 mlx_get_data_addr as an int* and store it in an int*.
	 This way, the array will have the exact same size as your window, and each index
	 will represent one complete color of a pixel !
	*/

	count_h = 0;
	while (count_h < IMG_HEIGHT) // 여기서 ++을 해주는듯
	{
		count_w = 0;
		while (count_w < IMG_WIDTH)
		{
			// img.data 가 1차원 배열로 되어 있는 것으로 유추했을 때
			// 우리가 창으로 보는 image가 2차원이지만, 사실은 1차원인 픽셀이 늘어져있는 줄인 것같다.
			if (count_w % 2 == 1) // count_w가 홀수이면 하얀색
				img.data[count_h * IMG_WIDTH + count_w] = 0xFFFFFF; // img.data의 배열에 픽셀 색 값을 넣어주는 듯,
			else // count_w가 짝수이면 초록색
				img.data[count_h * IMG_WIDTH + count_w] = 0x6AA84F;
			// img.data 배열이 어떻게 만들어져있을까? 왜 1차원 배열인데 넓이와 높이를 더해서 픽셀의 색 값이 정해질까? --> 픽셀 찍을 때 1차원으로 저장되서 2차원으로 출력됨

			count_w++;
		}
		count_h++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, img.img_ptr, 0, 0); // 이미지 포인터를 파라미터로 넣어 그 이미지 위치를 정해준다.
	// 그런데, win도 필요하고 mlx_ptr도 필요하구나. win은 어떤 window창에 띄울 건지, mlx_ptr은 mlx를 활용한 함수를 사용하게
	// 되면 그냥 무조건 필요한 것같다.
	mlx_loop(mlx->mlx_ptr);
	return (0);
}