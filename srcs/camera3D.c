#include "../includes/headers/cub3d.h"

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
} t_ray;

typedef struct s_slice
{
	int	height;
	int	start;
	int	end;
	int	color;
} t_slice;

void	camera3D(t_session *instance, double pos_x, double pos_y)
{

	t_camera3D	camera;
	t_ray		ray;
	t_slice		slice;
	int	i;

	// setup camera
	camera.dir_x = cos(instance->player.angle * (PI / 180));
	camera.dir_y = sin(instance->player.angle * (PI / 180));
	camera.fov = 72 * (PI / 180); // Field of view in radians
	camera.plane_x = -camera.dir_y * tan(camera.fov / 2);
	camera.plane_y = camera.dir_x * tan(camera.fov / 2);

	i = 0;
	while (i < W_WIDTH) //i < n_rays
	{
		// setup values for dda
		ray.x = (int)pos_x;
		ray.y = (int)pos_y;
		camera.x = 2 * i / (double)W_WIDTH - 1;
		ray.ray_dir_x = camera.dir_x + camera.plane_x * camera.x;
		ray.ray_dir_y = camera.dir_y + camera.plane_y * camera.x;

		if (ray.ray_dir_y == 0)
			ray.delta_dist_x = W_WIDTH;
		else
			ray.delta_dist_x = fabs(1 / ray.ray_dir_x);

		if (ray.ray_dir_x == 0)
			ray.delta_dist_y = W_WIDTH;
		else
			ray.delta_dist_y = fabs(1 / ray.ray_dir_y);

		if (ray.ray_dir_x < 0)
		{
			ray.step_x = -1;
			ray.side_dist_x = (pos_x - ray.x) * ray.delta_dist_x;
		}
		else
		{
			ray.step_x = 1;
			ray.side_dist_x = (ray.x + 1.0 - pos_x) * ray.delta_dist_x;
		}
		if (ray.ray_dir_y < 0)
		{
			ray.step_y = -1;
			ray.side_dist_y = (pos_y - ray.y) * ray.delta_dist_y;
		}
		else
		{
			ray.step_y = 1;
			ray.side_dist_y = (ray.y + 1.0 - pos_y) * ray.delta_dist_y;
		}
		// exec dda until collision
		ray.hit = 0;
		while (ray.hit == 0)
		{
			if (ray.side_dist_x < ray.side_dist_y)
			{
				ray.side_dist_x += ray.delta_dist_x;
				ray.x += ray.step_x;
				ray.side = 0;
			}
			else
			{
				ray.side_dist_y += ray.delta_dist_y;
				ray.y += ray.step_y;
				ray.side = 1;
			}
			//pixel_put(&instance->mlx_img, x, y, 0xFF0000); // check ray in 2Debug
			if (instance->map.grid[ray.y][ray.x] == '1')
				ray.hit = 1;
		}
		if (ray.side == 0)
			ray.perp_wall_dist = (ray.side_dist_x - ray.delta_dist_x);
		else
			ray.perp_wall_dist = (ray.side_dist_y - ray.delta_dist_y);

		//render vertical slices from left to right
		if (ray.perp_wall_dist > 0)
		{
			slice.height = (int)(W_HEIGHT / ray.perp_wall_dist * MAP_SCALE);
			slice.start = -slice.height / 2 + W_HEIGHT / 2;
			slice.end = slice.height / 2 + W_HEIGHT / 2;
			if (slice.start < 0)
				slice.start = 0;
			if (slice.end >= W_HEIGHT)
				slice.end = W_HEIGHT - 1;
			slice.color = 0x7c71c4;
			if (ray.side == 1)
				slice.color = 0x2f4f4f;
			draw_line(instance, (t_point){i, slice.start}, (t_point){i, slice.end}, slice.color);
			}
			i++;
	}
}
