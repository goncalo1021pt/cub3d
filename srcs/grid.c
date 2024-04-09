
#include "../includes/headers/cub3d.h"

void draw_square(t_session *instance, t_point point, int sq, int color)
{
	t_point	start;
	t_point end;

	// Draw top border
	start = point;
	end.x = point.x + sq;
	end.y = point.y;
	draw_line(instance, start, end, color);
	// Draw left border
	end.x = point.x;
	end.y = point.y + sq;
	draw_line(instance, start, end, color);
	// Draw bottom border
	start.x = point.x;
	start.y = point.y + sq;
	end.x = point.x + sq;
	end.y = point.y + sq;
	draw_line(instance, start, end, color);
	// Draw right border
	start.x = point.x + sq;
	start.y = point.y;
	end.x = point.x + sq;
	end.y = point.y + sq;
	draw_line(instance, start, end, color);
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

void	draw_player(t_session *instance, int x, int y)
{
	t_point	pos;
	int		sq;

	sq = MAP_SCALE / 4;
	pos.y = y - (sq / 2);
	pos.x = x - (sq / 2);
	draw_square(instance, pos, sq, 0x6c71c4);
	draw_face(instance, x, y, 0x6c71c4);
}

void draw_grid(t_session *instance)
{
	t_point		top;
	int			sq;
	int			y;
	int			x;

	sq = MAP_SCALE;
	y = 0;
	while (instance->map.map[y])
	{
		x = 0;
		while (instance->map.map[y][x])
		{
			top.y = y * sq;
			top.x = x * sq;
			if (instance->map.map[y][x] == '1')
				draw_square(instance, top, sq, 0x100000);
			x++;
		}
		y++;
	}
}

void	draw_scaled(t_session *instance)
{
	int			y;
	int			x;
	//t_camera2d	cam2d;

	y = 0;
	//init_camera2d(instance, &cam2d);
	while (instance->map.grid[y])
	{
		x = 0;
		while (instance->map.grid[y][x])
		{
			if (instance->map.grid[y][x] == '1')
				pixel_put(&(instance->mlx_img), x, y, 0xff4500);
			else if (instance->map.grid[y][x] == '0')
				pixel_put(&(instance->mlx_img), x, y, 0xffffff);
			x++;
		}
		y++;
	}
	draw_grid(instance);
	draw_player(instance, instance->player.x, instance->player.y);
}

