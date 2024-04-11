
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

void draw_grid(t_session *instance)
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
			if (instance->map.grid[y][x] == '1' && (x % MAP_SCALE == 0 && y % MAP_SCALE == 0))
				draw_square(instance, ((t_point){x, y}), MAP_SCALE, 0x000000);
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

