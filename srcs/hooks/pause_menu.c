#include "../../includes/headers/cub3d.h"

int	interpolate(float ratio, int start, int end)
{
	return (start * (1 - ratio) + end * ratio);
}

int	create_rgb(float ratio, int start, int end)
{
	int	r;
	int	g;
	int	b;

	r = interpolate(ratio, (start >> 16) & 0xFF, (end >> 16) & 0xFF);
	g = interpolate(ratio, (start >> 8) & 0xFF, (end >> 8) & 0xFF);
	b = interpolate(ratio, start & 0xFF, end & 0xFF);
	return ((r << 16) | (g << 8) | b);
}

void	pause_menu(t_session *instance)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	while (x < instance->width)
	{
		y = 0;
		while (y < instance->height)
		{
			color = get_pixel(&instance->mlx_img, x, y);
			pixel_put(instance, x, y, create_rgb(0.6, color, 0x000000));
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(instance->mlx_ser, instance->mlx_win,
		instance->mlx_img.img, 0, 0);
}
