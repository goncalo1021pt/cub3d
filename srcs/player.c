#include "../includes/headers/cub3d.h"

void	cast_ray(t_session *instance, t_point start, t_point end, int color)
{
	t_dda	dda;
	t_point	r_pos;
	int		i;

	i = 0;
	init_dda(&dda, start, end);
	while (i <= dda.step)
	{
		r_pos.y = dda.current_y;
		r_pos.x = dda.current_x;
		if (instance->map.grid[r_pos.y][r_pos.x] == '1')
			return;
		pixel_put(&instance->mlx_img, dda.current_x, dda.current_y, color);
		dda.current_x += dda.x_inc;
		dda.current_y += dda.y_inc;
		i++;
	}
}

void draw_face(t_session *instance, int x, int y, int color)
{
	int		length;
	t_point	end;

	length = MAP_SCALE / 4;
	end.y = y + length * sin(instance->player.angle * PI / 180);
	end.x = x + length * cos(instance->player.angle * PI / 180);
	draw_line(instance, (t_point){x, y}, (t_point){end.x, end.y}, color);
}

void draw_ray(t_session *instance, int x, int y, int color)
{
	int		length;
	t_point	end;

	length = W_WIDTH;
	end.y = y + length * sin(instance->player.angle * PI / 180);
	end.x = x + length * cos(instance->player.angle * PI / 180);
	cast_ray(instance, (t_point){x, y}, (t_point){end.x, end.y}, color);
}

void	draw_player(t_session *instance, int x, int y)
{
	t_point	pos;
	int		sq;

	sq = MAP_SCALE / 4;
	pos.y = y - (sq / 2);
	pos.x = x - (sq / 2);
	draw_square(instance, pos, sq, 0x6c71c4);
	draw_ray(instance, x, y, 0x6c71c4);
	draw_face(instance, x, y, 0x2501c4);
}