/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:45:06 by rlandolt          #+#    #+#             */
/*   Updated: 2024/04/26 13:17:39 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/cub3d.h"

void	init_camera2d(t_session *instance, t_camera2d *cam2d)
{
	cam2d->size.x = instance->width / 5;
	cam2d->size.y = instance->height / 5;
	cam2d->p_pos.x = instance->player.x;
	cam2d->p_pos.y = instance->player.y;
	cam2d->top_l.x = fmax(0, instance->player.x - cam2d->size.x / 2);
	cam2d->top_l.y = fmax(0, instance->player.y - cam2d->size.y / 2);
	cam2d->bot_r.x = fmin(instance->map.grid_w, instance->player.x
			+ cam2d->size.x / 2);
	cam2d->bot_r.y = fmin(instance->map.grid_h, instance->player.y
			+ cam2d->size.y / 2);
	cam2d->h_scale = instance->height / 7;
	cam2d->w_scale = instance->width / 8;
}

void	vp_player(t_session *instance, int x, int y)
{
	t_point	pos;
	int		sq;

	sq = 16;
	pos.y = y - (sq / 2);
	pos.x = x - (sq / 2);
	fill_square(instance, pos, sq, 0x000000);
	draw_square(instance, pos, sq, 0xffffff);
	draw_face(instance, x, y, 0xff4500);
}

void	vp_scaled(t_session *instance)
{
	t_camera2d	cam;

	if (instance->mode.type == PLAY && instance->mode.sub != MINIMAP)
		return ;
	init_camera2d(instance, &cam);
	cam.p = instance->player;
	cam.y = cam.top_l.y - 1;
	while (++cam.y < cam.bot_r.y && instance->map.grid[cam.y])
	{
		cam.off.y = (cam.y - cam.top_l.y)
			+ (cam.h_scale - (cam.p.y - cam.top_l.y));
		cam.x = cam.top_l.x - 1;
		while (++cam.x < cam.bot_r.x && instance->map.grid[cam.y][cam.x])
		{
			cam.off.x = (cam.x - cam.top_l.x)
				+ (cam.w_scale - (cam.p.x - cam.top_l.x));
			cam.color = get_pixel(&instance->mlx_img, cam.off.x, cam.off.y);
			if (instance->map.grid[cam.y][cam.x] == '1')
				pixel_put(instance, cam.off.x, cam.off.y, cam.color + 0xf0f010);
			else if (instance->map.grid[cam.y][cam.x] == '0')
				pixel_put(instance, cam.off.x, cam.off.y, cam.color + 0x004550);
		}
	}
	vp_player(instance, cam.w_scale, cam.h_scale);
}
