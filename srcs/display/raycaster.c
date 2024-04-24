#include "../../includes/headers/cub3d.h"

void	init_ray(t_camera3D *camera, t_ray *ray, int i, double pos_x, double pos_y)
{
	ray->x = pos_x;
	ray->y = pos_y;
	camera->x = 2 * i / (double)W_WIDTH - 1;
	ray->ray_dir_x = camera->dir_x + camera->plane_x * camera->x;
	ray->ray_dir_y = camera->dir_y + camera->plane_y * camera->x;
	ray->delta_dist_x = clamp_ray(ray->ray_dir_x);
	ray->delta_dist_y = clamp_ray(ray->ray_dir_y);
}

void	aim_ray(t_ray *ray, double pos_x, double pos_y)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (pos_x - ray->x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->x + 1.0 - pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (pos_y - ray->y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->y + 1.0 - pos_y) * ray->delta_dist_y;
	}
}

void	cast_ray(t_session *instance, t_ray	*ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->y += ray->step_y;
			ray->side = 1;
		}
		if (!instance->map.grid[ray->y] || !instance->map.grid[ray->y][ray->x]
			|| instance->map.grid[ray->y][ray->x] == '1' || instance->map.grid[ray->y][ray->x] == ' ')
		{
			ray->wall_dir = get_wall_dir(instance->map.grid, ray->x, ray->y, ray->side);
			hit = 1;
		}
	}
	ray->perp_wall_dist = get_pwall_distance(ray);
}