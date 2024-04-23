#include "../../includes/headers/cub3d.h"

void	init_camera3D(t_session *instance, t_camera3D *camera)
{
	camera->dir_x = cos(instance->player.angle * (PI / 180));
	camera->dir_y = sin(instance->player.angle * (PI / 180));
	camera->fov = 78 * (PI / 180);
	camera->plane_x = -camera->dir_y * tan(camera->fov / 2);
	camera->plane_y = camera->dir_x * tan(camera->fov / 2);
}

void draw_textured_line(t_session *instance, t_point start, t_point end, t_texture *tex)
{
	t_dda dda;
	int i;

	i = 0;
	init_dda(&dda, start, end);
	i = -dda.current_y / dda.y_inc;
	dda.current_y = 0;
	tex->x = tex->wall_x * tex->data->width / MAP_SCALE;
	while (i <= dda.step)
	{
		tex->y = (i / dda.step) * tex->data->height;
		if (tex->y >= 0 && tex->y <= tex->data->height
			&& dda.current_y >= 0 && dda.current_y <= instance->height)
		{
			tex->color = get_pixel(tex->data, tex->x, tex->y);
			pixel_put(instance, dda.current_x, dda.current_y, tex->color);
		}
		dda.current_y += dda.y_inc;
		if (dda.current_y > instance->height)
			break;
		i++;
	}
}

void	camera3d(t_session *instance, double pos_x, double pos_y)
{
	t_camera3D	camera;
	t_ray		ray;
	t_slice		slice;
	t_texture	tex;
	int	i;

	init_camera3D(instance, &camera);
	i = 0;
	while (i < instance->width)
	{
		init_ray(&camera, &ray, i, (t_point){pos_x, pos_y});
		aim_ray(&ray, pos_x, pos_y);
		cast_ray(instance, &ray);
		slice.height = (int)(instance->height / ray.perp_wall_dist * MAP_SCALE);
		slice.start = -slice.height / 2 + instance->height / 2;
		slice.end = slice.height / 2 + instance->height / 2;
		if (ray.wall_dir == EAST_TEXTURE || ray.wall_dir == WEST_TEXTURE)
			ray.wall_x = pos_y + ray.perp_wall_dist * ray.ray_dir_y ;
		else
			ray.wall_x = pos_x + ray.perp_wall_dist * ray.ray_dir_x ;
		tex.wall_x = floor(ray.wall_x % MAP_SCALE);
		tex.data = get_tex_data(instance, &ray);
		draw_textured_line(instance, (t_point){i, slice.start}, (t_point){i, slice.end}, &tex);
		i++;
	}
}
