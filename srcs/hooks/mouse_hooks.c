/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:45:56 by rlandolt          #+#    #+#             */
/*   Updated: 2024/04/26 12:45:58 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/cub3d.h"

int	mouse_movement(int x, int y, t_session *instance)
{
	int	dif;

	(void)y;
	if (instance->mode.type == PAUSE)
		return (0);
	dif = abs(instance->width - x);
	if (x > (instance->width / 2))
		instance->player.angle += (dif / MOUSE_SENSITIVITY);
	else if (x < (instance->width / 2))
		instance->player.angle -= dif / MOUSE_SENSITIVITY;
	mlx_mouse_move(instance->mlx_ser, instance->mlx_win, instance->width / 2,
		instance->height / 2);
	return (0);
}

int	ignore_mouse_keys(int button, int x, int y, t_session *instance)
{
	(void)button;
	(void)x;
	(void)y;
	(void)instance;
	return (0);
}
