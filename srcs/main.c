/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:44:49 by rlandolt          #+#    #+#             */
/*   Updated: 2024/03/28 19:21:49 by rlandolt         ###   ########.fr       */
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

typedef struct s_dda
{
	float	delta_x;
	float	delta_y;
	float	step;
	float	x_inc;
	float	y_inc;
	float	current_x;
	float	current_y;
}	t_dda;

void	init_dda(t_dda *dda, int start_y, int start_x , int end_y, int end_x)
{
	dda->current_x = start_x;
	dda->current_y = start_y;
	dda->delta_x = end_x - start_x;
	dda->delta_y = end_y - start_y;
	dda->step = fmax(fabs(dda->delta_x), fabs(dda->delta_y));
	dda->x_inc = dda->delta_x / dda->step;
	dda->y_inc = dda->delta_y / dda->step;
}

void	draw_line(t_session *instance, int start_x, int end_x, int start_y, int end_y)
{
	t_dda	dda;
	int		i;

	i = 0;
	init_dda(&dda, start_y, end_y, start_x, end_x);
	while (i <= dda.step)
	{
		mlx_pixel_put(instance->mlx_ser, instance->mlx_win, dda.current_x, dda.current_y, 0xff4500);
		dda.current_x += dda.x_inc;
		dda.current_y += dda.y_inc;
		i++;
	}
}

void draw_square(t_session *instance, int y, int x, int width, int height)
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
	int top_left_x;
	int top_left_y;

	for (y = 0; map[y] != NULL; y++)
	{
		for (x = 0; map[y][x] != '\0'; x++)
		{
			top_left_x = x * TILE_SIZE;
			top_left_y = y * TILE_SIZE;
			draw_square(instance, top_left_x, top_left_y, TILE_SIZE, TILE_SIZE);
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
