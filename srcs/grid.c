
#include "../includes/headers/cub3d.h"

void draw_square(t_session *instance, t_point point, t_square sq, int color)
{
	t_point	start;
	t_point end;

	// Draw top border
	start = point;
	end.x = point.x + sq.width;
	end.y = point.y;
	draw_line(instance, start, end, color);
	// Draw left border
	end.x = point.x;
	end.y = point.y + sq.height;
	draw_line(instance, start, end, color);
	// Draw bottom border
	start.x = point.x;
	start.y = point.y + sq.height;
	end.x = point.x + sq.width;
	end.y = point.y + sq.height;
	draw_line(instance, start, end, color);
	// Draw right border
	start.x = point.x + sq.width;
	start.y = point.y;
	end.x = point.x + sq.width;
	end.y = point.y + sq.height;
	draw_line(instance, start, end, color);
}

void	draw_player(t_session *instance)
{
	printf("pĺayer -> x: %d y: %d\n", instance->player.x, instance->player.y);
	pixel_put(&instance->mlx_img, instance->player.x, instance->player.y, 0x25f7ff);
}

void	draw_scaled(t_session *instance)
{
	int			y;
	int			x;

	y = 0;
	while (instance->map.grid[y])
	{
		x = 0;
		while (instance->map.grid[y][x])
		{
			if (instance->map.grid[y][x] == '1')
				pixel_put(&(instance->mlx_img), x, y, 0xff4500);
			else if (instance->map.grid[y][x] == 'P')
			{
				printf("grid -> x: %d y: %d\n", x, y);
				draw_player(instance);
				pixel_put(&(instance->mlx_img), x, y, 0xff4500);
			}
			x++;
		}
		y++;
	}
	draw_grid(instance);
}

void draw_grid(t_session *instance)
{
	t_point		top;
	t_square	sq;
	int			y;
	int			x;

	sq.height = MAP_SCALE;
	sq.width = MAP_SCALE;
	y = 0;
	while (instance->map.map[y])
	{
		x = 0;
		while (instance->map.map[y][x])
		{
			top.y = y * sq.height;
			top.x = x * sq.width;
			if (instance->map.map[y][x] == '1')
				draw_square(instance, top, sq, 0x100000);
			x++;
		}
		y++;
	}
}

