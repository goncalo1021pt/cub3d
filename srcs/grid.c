
#include "../includes/headers/cub3d.h"

size_t arr_size(char **arr)
{
	size_t size;

	size = 0;
	while (arr[size])
		size++;
	return (size);
}

size_t longest_strlen(char **arr)
{
	size_t max;
	size_t len;
	size_t i;

	i = 0;
	max = 0;
	while (arr[i])
	{
		len = ft_strlen(arr[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

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

void	draw_scaled(t_session *instance)
{
	int	y = 0;
	int x = 0;

	while (instance->map.grid[y])
	{
		x = 0;
		while (instance->map.grid[y][x])
		{
			if (instance->map.grid[y][x] == '1')
				pixel_put(&(instance->mlx_img), x, y, 0xff4500);
			else if (instance->map.grid[y][x] == 'P')
				pixel_put(&(instance->mlx_img), x, y, 0xffffff);
			x++;
		}
		y++;
	}
	draw_grid(instance);
}

void draw_grid(t_session *instance)
{
	t_grid	grid;

	grid.pt.y = 0;
	//grid.col_s = arr_size(instance->map.map);
	//grid.row_s = longest_strlen(instance->map.map);
	grid.sq.height = MAP_SCALE;//(W_HEIGHT - 1) / grid.col_s;
	grid.sq.width = MAP_SCALE;//(W_WIDTH - 1)/ grid.row_s;
	while(instance->map.map[grid.pt.y])
	{
		grid.pt.x = 0;
		while(instance->map.map[grid.pt.y][grid.pt.x])
		{
			grid.top.y = grid.pt.y * grid.sq.height;
			grid.top.x = grid.pt.x * grid.sq.width;
			if (instance->map.map[grid.pt.y][grid.pt.x] == '1')
				draw_square(instance, grid.top, grid.sq, 0x000000);
			grid.pt.x++;
		}
		grid.pt.y++;
	}
}

void	draw_player(t_session *instance)
{
	pixel_put(&instance->mlx_img, instance->player.x, instance->player.x, 0xffffff); 
}

/*
t_point spawn_point(t_session *instance)
{
	t_grid	grid;
	t_point	pos;

	grid.pt.y = 0;
	grid.col_s = arr_size(instance->map.map);
	grid.row_s = longest_strlen(instance->map.map);
	grid.sq.height = MAP_SCALE;//(W_HEIGHT - 1) / grid.col_s;
	grid.sq.width = MAP_SCALE;//(W_WIDTH - 1)/ grid.row_s;
	while(instance->map.map[grid.pt.y])
	{
		grid.pt.x = 0;
		while(instance->map.map[grid.pt.y][grid.pt.x])
		{
			grid.top.y = grid.pt.y * grid.sq.height;
			grid.top.x = grid.pt.x * grid.sq.width;
			if (instance->map.map[grid.pt.y][grid.pt.x] == '0') // find first avaible square
			{
				pos.y = grid.top.y + grid.sq.height / 2;
				pos.x = grid.top.x + grid.sq.width / 2;
				return (pos);
			}
			grid.pt.x++;
		}
		grid.pt.y++;
	}
	pos.y = -1;
	pos.x = -1;
	return (pos);
}
*/