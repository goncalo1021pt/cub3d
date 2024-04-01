
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

void draw_grid(t_session *instance, char **map)
{
	t_grid	grid;

	grid.y = 0;
	grid.col_s = arr_size(map);
	grid.row_s = longest_strlen(map);
	grid.sq_h = (W_HEIGHT - 1) / grid.col_s;
	grid.sq_w = (W_WIDTH - 1)/ grid.row_s;
	while(map[grid.y])
	{
		grid.x = 0;
		while(map[grid.y][grid.x])
		{
			grid.top_y = grid.y * grid.sq_h;
			grid.top_x = grid.x * grid.sq_w;
			if (map[grid.y][grid.x] == '1')
				draw_square(instance, grid.top_x, grid.top_y, grid.sq_w, grid.sq_h);
			grid.x++;
		}
		grid.y++;
	}
}
