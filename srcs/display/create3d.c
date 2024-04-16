#include "../../includes/headers/cub3d.h"

void cast_3d(t_session *instance)
{
	int x;
	int y;

	y = (W_HEIGHT / 2) -1;
	while (++y < (W_HEIGHT / 2))
	{
		x = -1;
		while (++x != W_WIDTH)
		{
			pixel_put(&(instance->mlx_img), x, y, 0x7FFF00);
		}
	}
}