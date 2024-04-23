#include "../../includes/headers/cub3d.h"

int	get_pixel(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	return (*(unsigned int *)dst);
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
// 		y_scale = (texture.data.height * texture.line_h) / MAP_SCALE;
// 		color = get_pixel(&texture.data, x_scale, y_scale);
// 		pixel_put(&instance->mlx_img, dda.current_x, dda.current_y, color);
// 		dda.current_x += dda.x_inc;
// 		dda.current_y += dda.y_inc;
// 		i++;
// 	}
// }
