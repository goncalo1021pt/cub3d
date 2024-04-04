
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

void draw_square(t_session *instance, int x, int y, int width, int height)
{
	// Draw top border
	draw_line(instance, x, y, x + width, y);
	// Draw left border
	draw_line(instance, x, y, x, y + height);
	// Draw bottom border
	draw_line(instance, x, y + height, x + width, y + height);
	// Draw right border
	draw_line(instance, x + width, y, x + width, y + height);
}

void draw_grid(t_session *instance)
{
	t_grid	grid;

	grid.y = 0;
	grid.col_s = arr_size(instance->map.map);
	grid.row_s = longest_strlen(instance->map.map);
	grid.sq_h = MAP_SCALE;//(W_HEIGHT - 1) / grid.col_s;
	grid.sq_w = MAP_SCALE;//(W_WIDTH - 1)/ grid.row_s;
	while(instance->map.map[grid.y])
	{
		grid.x = 0;
		while(instance->map.map[grid.y][grid.x])
		{
			grid.top_y = grid.y * grid.sq_h;
			grid.top_x = grid.x * grid.sq_w;
			if (instance->map.map[grid.y][grid.x] == '1')
				draw_square(instance, grid.top_x, grid.top_y, grid.sq_w, grid.sq_h);
			grid.x++;
		}
		grid.y++;
	}
}

void	draw_player(t_session *instance, t_point pos)
{
	if (pos.y >= 0 && pos.y >= 0)
		pixel_put(&instance->mlx_img, pos.x, pos.y, 0xffffff); 
}

t_point spawn_point(t_session *instance)
{
	t_grid	grid;
	t_point	pos;

	grid.y = 0;
	grid.col_s = arr_size(instance->map.map);
	grid.row_s = longest_strlen(instance->map.map);
	grid.sq_h = MAP_SCALE;//(W_HEIGHT - 1) / grid.col_s;
	grid.sq_w = MAP_SCALE;//(W_WIDTH - 1)/ grid.row_s;
	while (instance->map.map[grid.y])
	{
		grid.x = 0;
		while (instance->map.map[grid.y][grid.x])
		{
			grid.top_y = grid.y * grid.sq_h;
			grid.top_x = grid.x * grid.sq_w;
			if (instance->map.map[grid.y][grid.x] == '0') // find first avaible square
			{
				pos.y = grid.top_y + grid.sq_h / 2;
				pos.x = grid.top_x + grid.sq_w / 2;
				return (pos);
			}
			grid.x++;
		}
		grid.y++;
	}
	pos.y = -1;
	pos.x = -1;
	return (pos);
}