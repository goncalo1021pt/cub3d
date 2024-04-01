
#include "../includes/headers/cub3d.h"

void	init_dda(t_dda *dda, int start_x, int start_y , int end_x, int end_y)
{
	dda->current_x = start_x;
	dda->current_y = start_y;
	dda->delta_x = end_x - start_x;
	dda->delta_y = end_y - start_y;
	dda->step = fmax(fabs(dda->delta_x), fabs(dda->delta_y));
	dda->x_inc = dda->delta_x / dda->step;
	dda->y_inc = dda->delta_y / dda->step;
}

void	draw_line(t_session *instance, int start_x, int end_x, int start_y, int end_y)
{
	t_dda	dda;
	int		i;

	i = 0;
	init_dda(&dda, start_y, end_y, start_x, end_x);
	while (i <= dda.step)
	{
		pixel_put(&instance->mlx_img, dda.current_x, dda.current_y, 0xff4500);
		dda.current_x += dda.x_inc;
		dda.current_y += dda.y_inc;
		i++;
	}
}
