#include "../../includes/headers/cub3d.h"

double	clamp_ray(double dir)
{
	if (dir == 0)
		return (W_WIDTH);
	else
		return (fabs(1 / dir));
}

int	clamp_slice(int slice) // no need
{
	if (slice < 0)
		return (0);
	if (slice >= W_HEIGHT)
		return (W_HEIGHT - 1);
	return (slice);
}

int get_wall_dir(char **grid ,int x, int y, int side)
{
	if (grid[y + 1][x] != '1' && side == 1)
		return (SOUTH_TEXTURE);
	else if (grid[y - 1][x] != '1' && side == 1)
		return (NORTH_TEXTURE);
	else if (grid[y][x + 1] != '1' )
		return (EAST_TEXTURE);
	else
		return (WEST_TEXTURE);
}

void	init_camera3D(t_session *instance, t_camera3D *camera)
{
	camera->dir_x = cos(instance->player.angle * (PI / 180));
	camera->dir_y = sin(instance->player.angle * (PI / 180));
	camera->fov = 78 * (PI / 180);
	camera->plane_x = -camera->dir_y * tan(camera->fov / 2);
	camera->plane_y = camera->dir_x * tan(camera->fov / 2);
}

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
		//pixel_put(&instance->mlx_img, ray->x, ray->y, 0xFF0000); // check ray in 2Debug
		if (!instance->map.grid[ray->y] || !instance->map.grid[ray->y][ray->x]
			|| instance->map.grid[ray->y][ray->x] == '1' || instance->map.grid[ray->y][ray->x] == ' ')
		{
			ray->wall_dir = get_wall_dir(instance->map.grid, ray->x, ray->y, ray->side);
			hit = 1;
		}
	}
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x); // one func to return value
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
}

void draw_textured_line(t_session *instance, t_point start, t_point end, t_texture *texture)
{
	t_dda dda;
	int i;
	int	tex_x;
	int	tex_y;
	int color;

	i = 0;
	init_dda(&dda, start, end);
	while (dda.current_y < 0)
	{
		dda.current_y += dda.y_inc;
		i++;
	}
	tex_x = texture->x * texture->data.width / MAP_SCALE;
	while (i <= dda.step)
	{
		tex_y = (i / dda.step) * texture->data.height;
		if (tex_y >= 0 && tex_y <= texture->data.height
			&& dda.current_y > 0 && dda.current_y < W_HEIGHT)
		{
			color = get_pixel(&texture->data, tex_x, tex_y);
			pixel_put(&(instance->mlx_img), dda.current_x, dda.current_y, color);
		}
		dda.current_y += dda.y_inc;
		if (dda.current_y > W_HEIGHT)
			break;
		i++;
	}
}

void	camera3D(t_session *instance, double pos_x, double pos_y)
{
	t_camera3D	camera;
	t_ray		ray;
	t_slice		slice;
	t_texture	tex;
	int	i;

	init_camera3D(instance, &camera);
	i = 0;
	while (i < W_WIDTH) //i < n_rays
	{
		init_ray(&camera, &ray, i, pos_x, pos_y);
		aim_ray(&ray, pos_x, pos_y);
		cast_ray(instance, &ray);
		if (ray.perp_wall_dist > 0)
		{
			slice.height = (int)(W_HEIGHT / ray.perp_wall_dist * MAP_SCALE);
			slice.start = -slice.height / 2 + W_HEIGHT / 2;
			slice.end = slice.height / 2 + W_HEIGHT / 2;
			//slice.start = clamp_slice(slice.start);
			//slice.end = clamp_slice(slice.end);



			tex.slice_height = slice.height; // no need
			if (ray.wall_dir == EAST_TEXTURE || ray.wall_dir == WEST_TEXTURE)
				ray.wall_x = pos_y + ray.perp_wall_dist * ray.ray_dir_y ;
			else
				ray.wall_x = pos_x + ray.perp_wall_dist * ray.ray_dir_x ;
			//ray.wall_x = floor(ray.wall_x);
			ray.wall_x = floor(ray.wall_x % MAP_SCALE);
			tex.x = ray.wall_x;



			if (ray.wall_dir == NORTH_TEXTURE)
				tex.data = instance->textures[NORTH_TEXTURE];
			else if (ray.wall_dir == SOUTH_TEXTURE)
				tex.data = instance->textures[SOUTH_TEXTURE];
			else if (ray.wall_dir == EAST_TEXTURE)
				tex.data = instance->textures[EAST_TEXTURE];
			else if (ray.wall_dir == WEST_TEXTURE)
				tex.data = instance->textures[WEST_TEXTURE];
			draw_textured_line(instance, (t_point){i, slice.start}, (t_point){i, slice.end}, &tex);
		}
		i++;
	}
}


// void	camera3D(t_session *instance, double pos_x, double pos_y)
// {
// 	t_camera3D	camera;
// 	t_ray		ray;
// 	t_slice		slice;
// 	int	i;

// 	init_camera3D(instance, &camera);
// 	i = 0;
// 	while (i < W_WIDTH) //i < n_rays
// 	{
// 		init_ray(&camera, &ray, i, pos_x, pos_y);
// 		aim_ray(&ray, pos_x, pos_y);
// 		cast_ray(instance, &ray);
// 		if (ray.perp_wall_dist > 0)
// 		{
// 			slice.height = (int)(W_HEIGHT / ray.perp_wall_dist * MAP_SCALE);
// 			slice.start = -slice.height / 2 + W_HEIGHT / 2;
// 			slice.end = slice.height / 2 + W_HEIGHT / 2;
// 			slice.start = clamp_slice(slice.start);
// 			slice.end = clamp_slice(slice.end);
// 			// texture.line_h = ray.perp_wall_dist * MAP_SCALE;
// 			if (ray.wall_dir == NORTH_TEXTURE)
// 				slice.color = 0x8fbc8f;
// 			else if (ray.wall_dir == SOUTH_TEXTURE)
// 				slice.color = 0x2e8b57;
// 			else if (ray.wall_dir == EAST_TEXTURE)
// 				slice.color = 0x3cb371;
// 			else if (ray.wall_dir == WEST_TEXTURE)
// 				slice.color = 0x20b2aa;
// 			draw_line(instance, (t_point){i, slice.start}, (t_point){i, slice.end}, slice.color);
// 		}
// 		// printf("%d\n", ray.wall_x);
// 		i++;
// 	}
// }

