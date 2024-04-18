#include "../../includes/headers/cub3d.h"

typedef	struct s_camera3D
{
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	fov;
	double	x;
} t_camera3D;

typedef struct s_ray
{
	int hit;
	int side;
	int x;
	int y;
	double ray_dir_x;
	double ray_dir_y;
	double delta_dist_x;
	double delta_dist_y;
	double side_dist_x;
	double side_dist_y;
	double perp_wall_dist;
	double step_x;
	double step_y;
	int	wall_dir;
	int	wall_x;
} t_ray;

typedef struct s_slice
{
	int	height;
	int	start;
	int	end;
	int	color;
} t_slice;

double	clamp_ray(double dir)
{
	if (dir == 0)
		return (W_WIDTH);
	else
		return (fabs(1 / dir));
}

int	clamp_slice(int slice)
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

void	init_ray(t_camera3D *canera, t_ray *ray, int i, double pos_x, double pos_y)
{
	ray->x = (int)pos_x;
	ray->y = (int)pos_y;
	canera->x = 2 * i / (double)W_WIDTH - 1;
	ray->ray_dir_x = canera->dir_x + canera->plane_x * canera->x;
	ray->ray_dir_y = canera->dir_y + canera->plane_y * canera->x;
	ray->delta_dist_x = clamp_ray(ray->ray_dir_x);
	ray->delta_dist_y = clamp_ray(ray->ray_dir_y);
}

void	aim_ray(t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->x - ray->x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->x + 1.0 - ray->x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->y - ray->y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->y + 1.0 - ray->y) * ray->delta_dist_y;
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
	{
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
		ray->wall_x = ray->x % MAP_SCALE;
		// ray->wall_x = (ray->y + ray->perp_wall_dist + ray->ray_dir_y);
	}
	else
	{
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
		ray->wall_x = ray->y % MAP_SCALE;
		// ray->wall_x = ray->x + ray->perp_wall_dist + ray->ray_dir_x;
	}
	//ray->wall_x -= floor(ray->wall_x);
}

void	camera3D(t_session *instance, double pos_x, double pos_y)
{
	t_camera3D	camera;
	t_ray		ray;
	t_slice		slice;
	int	i;

	init_camera3D(instance, &camera);
	i = 0;
	while (i < W_WIDTH) //i < n_rays
	{
		init_ray(&camera, &ray, i, pos_x, pos_y);
		aim_ray(&ray);
		cast_ray(instance, &ray);
		if (ray.perp_wall_dist > 0)
		{
			slice.height = (int)(W_HEIGHT / ray.perp_wall_dist * MAP_SCALE);
			slice.start = -slice.height / 2 + W_HEIGHT / 2;
			slice.end = slice.height / 2 + W_HEIGHT / 2;
			slice.start = clamp_slice(slice.start);
			slice.end = clamp_slice(slice.end);
			if (ray.wall_dir == NORTH_TEXTURE)
				slice.color = 0x8fbc8f;
			else if (ray.wall_dir == SOUTH_TEXTURE)
				slice.color = 0x2e8b57;
			else if (ray.wall_dir == EAST_TEXTURE)
				slice.color = 0x3cb371;
			else if (ray.wall_dir == WEST_TEXTURE)
				slice.color = 0x20b2aa;
			draw_line(instance, (t_point){i, slice.start}, (t_point){i, slice.end}, slice.color);
		}
		// printf("%d\n", ray.wall_x);
		i++;
	}
}
