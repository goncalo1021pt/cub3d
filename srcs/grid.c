
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


void draw_square(t_session *instance, t_point start, t_square sq)
{
	// Draw top border
	draw_line(instance, start.x, start.y, start.x + sq.width, start.y);
	// Draw left border
	draw_line(instance, start.x, start.y, start.x, start.y + sq.height);
	// Draw bottom border
	draw_line(instance, start.x, start.y + sq.height, start.x + sq.width, start.y + sq.height);
	// Draw right border
	draw_line(instance, start.x + sq.width, start.y, start.x + sq.width, start.y + sq.height);
}

/*
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
*/

void draw_grid(t_session *instance)
{
	t_grid	grid;

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
			if (instance->map.map[grid.pt.y][grid.pt.x] == '1')
				draw_square(instance, grid.top, grid.sq);
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