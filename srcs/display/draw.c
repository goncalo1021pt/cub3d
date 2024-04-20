
#include "../../includes/headers/cub3d.h"

void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x > W_WIDTH - 1 || y > W_HEIGHT - 1)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	init_dda(t_dda *dda, t_point start, t_point end)
{
	dda->current_x = start.x;
	dda->current_y = start.y;
	dda->delta_x = end.x - start.x;
	dda->delta_y = end.y - start.y;
	dda->step = fmax(fabs(dda->delta_x), fabs(dda->delta_y));
	dda->x_inc = dda->delta_x / dda->step;
	dda->y_inc = dda->delta_y / dda->step;
}

void	draw_line(t_session *instance, t_point start, t_point end, int color)
{
	t_dda	dda;
	int		i;

	i = 0;
	init_dda(&dda, start, end);
	while (i <= dda.step)
	{
		pixel_put(&instance->mlx_img, dda.current_x, dda.current_y, color);
		dda.current_x += dda.x_inc;
		dda.current_y += dda.y_inc;
		i++;
	}
}

void	clear_image(t_session *instance)
{
	int	y;
	int	x;

	y = 0;
	mlx_clear_window(instance->mlx_ser, instance->mlx_win);
	while (y < instance->height)
	{
		x = 0;
		while (x < instance->width)
		{
			if (y < instance->height / 2)
				pixel_put(&(instance->mlx_img), x, y, instance->map.colors[0]);
			else
				pixel_put(&(instance->mlx_img), x, y, instance->map.colors[1]);
			x++;
		}
		y++;
	}
}

// void	draw_texture(t_session *instance, t_point start, t_point end, t_texture texture)
// {
// 	t_dda	dda;
// 	int		i;
// 	int color;
// 	int	x_scale;
// 	int	y_scale;

// 	x_scale = (texture.data.width * texture.x) / MAP_SCALE;
// 	init_dda(&dda, start, end);
// 	while (i <= dda.step)
// 	{
// 		y_scale = (texture.data.height * )
// 		color = get_pixel(&texture.data, x_scale, y_scale);
// 		pixel_put(&instance->mlx_img, dda.current_x, dda.current_y, color);
// 		dda.current_x += dda.x_inc;
// 		dda.current_y += dda.y_inc;
// 		i++;
// 	}
// }

