/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:44:10 by rlandolt          #+#    #+#             */
/*   Updated: 2024/04/01 15:18:10 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers/cub3d.h"

void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x > W_WIDTH - 1 || y > W_HEIGHT - 1)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	clear_image(t_session *instance, int color)
{
	int	y;
	int	x;

	y = 0;
	mlx_clear_window(instance->mlx_ser, instance->mlx_win);
	while (y < W_HEIGHT)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			pixel_put(&(instance->mlx_img), x, y, color);
			x++;
		}
		y++;
	}
}

void	mlx_shutdown(t_session *instance)
{
	mlx_loop_end(instance->mlx_ser);
	if (instance->mlx_img.img)
		mlx_destroy_image(instance->mlx_ser, instance->mlx_img.img);
	if (instance->mlx_win)
	{
		mlx_destroy_window(instance->mlx_ser, instance->mlx_win);
		instance->mlx_win = NULL;
	}
	if (instance->mlx_ser)
	{
		mlx_destroy_display(instance->mlx_ser);
		free(instance->mlx_ser);
	}
	free(instance);
	exit(0);
}

void	mlx_update(t_session *instance)
{
	clear_image(instance, 0x000000);
	draw_grid(instance);
	mlx_put_image_to_window(instance->mlx_ser,
		instance->mlx_win, instance->mlx_img.img, 0, 0);
}

void	mlx_startup(t_session *instance)
{
	instance->height = 0;
	instance->width = 0;
	instance->mlx_ser = mlx_init();
	instance->mlx_win = mlx_new_window(instance->mlx_ser, W_WIDTH, W_HEIGHT, "cub3d");
	instance->mlx_img.img = mlx_new_image(instance->mlx_ser, W_WIDTH, W_HEIGHT);
	instance->mlx_img.addr = mlx_get_data_addr(instance->mlx_img.img,
			&instance->mlx_img.bits_per_pixel, &instance->mlx_img.line_length,
			&instance->mlx_img.endian);
	if (!instance->mlx_ser || !instance->mlx_win || !instance->mlx_img.img)
		mlx_shutdown(instance);
	draw_grid(instance);
	draw_player(instance);
	mlx_put_image_to_window(instance->mlx_ser, instance->mlx_win, instance->mlx_img.img, 0, 0);
}
