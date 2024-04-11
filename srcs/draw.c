
#include "../includes/headers/cub3d.h"

void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x > W_WIDTH - 1 || y > W_HEIGHT - 1)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	clear_image(t_session *instance, int color)
{
	int	y;
	int	x;

	y = 0;
	mlx_clear_window(instance->mlx_ser, instance->mlx_win);
	while (y < W_HEIGHT)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			pixel_put(&(instance->mlx_img), x, y, color);
			x++;
		}
		y++;
	}
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

/*
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
*/