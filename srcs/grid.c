
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
	grid.col_s = arr_size(instance->map);
	grid.row_s = longest_strlen(instance->map);
	grid.sq_h = (W_HEIGHT - 1) / grid.col_s;
	grid.sq_w = (W_WIDTH - 1)/ grid.row_s;
	while(instance->map[grid.y])
	{
		grid.x = 0;
		while(instance->map[grid.y][grid.x])
		{
			grid.top_y = grid.y * grid.sq_h;
			grid.top_x = grid.x * grid.sq_w;
			if (instance->map[grid.y][grid.x] == '1')
				draw_square(instance, grid.top_x, grid.top_y, grid.sq_w, grid.sq_h);
			grid.x++;
		}
		grid.y++;
	}
}

// best to return player position to a vector2 variable and write different function to draw the player around that point?
void draw_player(t_session *instance)
{
	t_grid grid;

	grid.y = 0;
	grid.col_s = arr_size(instance->map);
	grid.row_s = longest_strlen(instance->map);
	grid.sq_h = (W_HEIGHT - 1) / grid.col_s;
	grid.sq_w = (W_WIDTH - 1) / grid.row_s;
	while (instance->map[grid.y])
	{
		grid.x = 0;
		while (instance->map[grid.y][grid.x])
		{
			grid.top_y = grid.y * grid.sq_h;
			grid.top_x = grid.x * grid.sq_w;
			if (instance->map[grid.y][grid.x] == '0') // find first avaible square
			{
				pixel_put(&instance->mlx_img, grid.top_x + grid.sq_w / 2, grid.top_y + grid.sq_h / 2, 0xffffff); // draw player at center of square xD
				return;
			}
			grid.x++;
		}
		grid.y++;
	}
}
