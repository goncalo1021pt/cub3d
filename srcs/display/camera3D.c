/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera3D.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:43:15 by rlandolt          #+#    #+#             */
/*   Updated: 2024/04/26 13:31:37 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/cub3d.h"

void	init_camera3d(t_session *instance, t_camera3D *camera)
{
	camera->dir_x = cos(instance->player.angle * (PI / 180));
	camera->dir_y = sin(instance->player.angle * (PI / 180));
	camera->fov = 78 * (PI / 180);
	camera->plane_x = -camera->dir_y * tan(camera->fov / 2);
	camera->plane_y = camera->dir_x * tan(camera->fov / 2);
}

int	get_pixel(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * 4);
	return (*(unsigned int *)dst);
}

void	draw_textured_line(t_session *instance, t_point start,
		t_point end, t_texture *tex)
{
	t_dda	dda;
	int		i;

	i = 0;
	init_dda(&dda, start, end);
	i = -dda.current_y / dda.y_inc;
	dda.current_y = 0;
	tex->x = tex->wall_x * tex->data->width / MAP_SCALE;
	while (i < dda.step)
	{
		tex->y = (i / dda.step) * tex->data->height;
		if (tex->y >= 0 && tex->y <= tex->data->height
			&& dda.current_y >= 0 && dda.current_y <= instance->height)
		{
			tex->color = get_pixel(tex->data, tex->x, tex->y);
			if (tex->color != 0xF900FF)
				pixel_put(instance, dda.current_x, dda.current_y, tex->color);
		}
		dda.current_y += dda.y_inc;
		if (dda.current_y > instance->height)
			break ;
		i++;
	}
}

typedef struct s_vector2
{
	double	x;
	double	y;
}	t_vector2;

void	rndr_doors(t_session *ist, t_camera3D camera, int i, t_vector2 pos)
{
	t_slice		slice;
	t_texture	tex;

	init_ray(&camera, &ist->aux_ray, i, (t_point){pos.x, pos.y});
	aim_ray(&ist->aux_ray, pos.x, pos.y);
	cast_aux_ray(ist, &ist->aux_ray);
	if (ist->aux_ray.perp_wall_dist <= 0)
		return ;
	slice.height = (int)(ist->height / ist->aux_ray.perp_wall_dist * MAP_SCALE);
	slice.start = -slice.height / 2 + ist->height / 2;
	slice.end = slice.height / 2 + ist->height / 2;
	ist->aux_ray.wall_x = get_walx(&ist->aux_ray, pos.x, pos.y);
	tex.wall_x = floor(ist->aux_ray.wall_x % MAP_SCALE);
	tex.data = get_tex_data(ist, &ist->aux_ray, true);
	draw_textured_line(ist, (t_point){i, slice.start},
		(t_point){i, slice.end}, &tex);
}

void	camera3d(t_session *ist, double pos_x, double pos_y)
{
	t_camera3D	camera;
	t_ray		ray;
	t_slice		slice;
	t_texture	tex;
	int			i;

	init_camera3d(ist, &camera);
	i = 0;
	while (i < ist->width)
	{
		init_ray(&camera, &ray, i, (t_point){pos_x, pos_y});
		aim_ray(&ray, pos_x, pos_y);
		cast_ray(ist, &ray);
		slice.height = (int)(ist->height / ray.perp_wall_dist * MAP_SCALE);
		slice.start = -slice.height / 2 + ist->height / 2;
		slice.end = slice.height / 2 + ist->height / 2;
		ray.wall_x = get_walx(&ray, pos_x, pos_y);
		tex.wall_x = floor(ray.wall_x % MAP_SCALE);
		tex.data = get_tex_data(ist, &ray, false);
		draw_textured_line(ist, (t_point){i, slice.start},
			(t_point){i, slice.end}, &tex);
		if (ray.door)
			rndr_doors(ist, camera, i, (t_vector2){pos_x, pos_y});
		i++;
	}
}
