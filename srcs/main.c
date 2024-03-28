/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:44:49 by rlandolt          #+#    #+#             */
/*   Updated: 2024/03/28 18:21:59 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x > W_WIDTH - 1 || y > W_HEIGHT - 1)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

#define TILE_SIZE 64

void draw_line(t_session *instance, int x0, int y0, int x1, int y1)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = dx - dy;

	while (x0 != x1 || y0 != y1)
	{
		mlx_pixel_put(instance->mlx_ser, instance->mlx_win, x0, y0, 0xFFFFFF); // Draw a white point
		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
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
	int x, y;

	for (y = 0; map[y] != NULL; y++)
	{
		for (x = 0; map[y][x] != '\0'; x++)
		{
			if (map[y][x] == '1' || map[y][x] == '0')
			{
				int top_left_x = x * TILE_SIZE;
				int top_left_y = y * TILE_SIZE;
				draw_square(instance, top_left_x, top_left_y, TILE_SIZE, TILE_SIZE);
			}
		}
	}
}


int	main(int argc, char **argv)
{
	t_session *instance;

	char* map[] = {
		"111111111",
		"100000001",
		"100000001",
		"100000001",
		"100000001",
		"111111111",
		NULL
	};
	(void)argv;
	if (argc == 2)
	{
		instance = (t_session *)malloc(sizeof(t_session));
		if (!instance)
			return (0);
		for (int i = 0; map[i] != NULL; i++)
			printf("%s\n", map[i]);
		mlx_startup(instance);
		mlx_key_hook(instance->mlx_win, handle_key, instance);
		mlx_hook(instance->mlx_win, DestroyNotify, StructureNotifyMask, exit_hook, instance);
		draw_grid(instance, map);
		mlx_loop(instance->mlx_ser);
	}
	return (0);
}
