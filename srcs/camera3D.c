#include "../includes/headers/cub3d.h"

/*
	double cam_angle;

	cam_angle = instance->player.angle * (PI / 180);
	dir_x = cos(cam_angle);
	dir_y = sin(cam_angle);
*/
void	camera3D(t_session *instance, double pos_x, double pos_y)
{
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;


	// dir_x = cos(instance->player.angle * (PI / 180));
	// dir_y = sin(instance->player.angle * (PI / 180));


	dir_x = 1;
	dir_y = 0;


	plane_x = 0;
	plane_y = 0.7;

	int	i;
	i = 0;
	while (i < W_WIDTH)
	{
		double cam_x;
		cam_x = 2 * i / (double)W_WIDTH - 1;

		double ray_dir_x;
		double ray_dir_y;
		ray_dir_x = dir_x + plane_x * cam_x;
		ray_dir_y = dir_y + plane_y * cam_x;


		int grid_x;
		int grid_y;
		grid_x = (int)pos_x;
		grid_y = (int)pos_y;

		double delta_dist_x;
		double delta_dist_y;
		delta_dist_x = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_x);	// Avoid division by zero
		delta_dist_y = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_y);	// Avoid division by zero

		double side_dist_x;
		double side_dist_y;
		double perp_wall_dist;
		double step_x;
		double step_y;
		int hit;
		int side;



		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (pos_x - grid_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (grid_x + 1.0 - pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (pos_y - grid_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (grid_y + 1.0 - pos_y) * delta_dist_y;
		}

		hit = 0;
		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				grid_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				grid_y += step_y;
				side = 1;
			}
			if (instance->map.grid[grid_y][grid_x] == '1')
				hit = 1;
		}

		if (side == 0)
			perp_wall_dist = (side_dist_x - delta_dist_x);
		else
			perp_wall_dist = (side_dist_y - delta_dist_y);

		int	line_height;
		int	line_start;
		int	line_end;
		int	color;

		line_height = (int)(W_HEIGHT / perp_wall_dist * MAP_SCALE);
		line_start = -line_height / 2 + W_HEIGHT / 2;
		line_end = line_height / 2 + W_HEIGHT / 2;
		if (line_start < 0)
			line_start = 0;
		if (line_end >= W_HEIGHT)
			line_end = W_HEIGHT - 1;
		color = 0xFFFFFF;
		if (side == 1)
			color = color / 2;
		draw_line(instance, (t_point){i, line_start}, (t_point){i, line_end}, color);
		i++;
	}
}
