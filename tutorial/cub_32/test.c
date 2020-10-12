#include "../minilibx/mlx.h"

void	load_tex(t_cub3d *cub3d, char *file, int i)
{
	int		x;
	int		y;

	y = 0;
	cub3d->map.tex[i].ptr = mlx_xpm_file_to_image(cub3d->wins.mlx, file, &cub3d->map.tex[i].x, &cub3d->map.tex[i].y);
	cub3d->map.tex[i].data = (int *)mlx_get_data_addr(cub3d->map.tex[i].ptr, &cub3d->map.tex[i].bpp, &cub3d->map.tex[i].size_l, &cub3d->map.tex[i].endian);
	cub3d->map.tex[i].bpp /= 8;
	cub3d->map.curr_tex[i] = (int *)ft_calloc((cub3d->map.tex[i].y * cub3d->map.tex[i].x), sizeof(int)); // 일자로 동적할당 addr 와 동일한 역할인듯
	// 여기 까지는 일반적인데,....
	while (y < cub3d->map.tex[i].y)
	{
		x = 0;
		while (x < cub3d->map.tex[i].x)
		{
			cub3d->map.curr_tex[i][(int)cub3d->map.tex[i].x * y + x] = cub3d->map.tex[i].data[cub3d->map.tex[i].x * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(cub3d->wins.mlx, cub3d->map.tex[i].ptr);
}
