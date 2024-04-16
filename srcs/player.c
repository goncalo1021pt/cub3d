#include "../includes/headers/cub3d.h"

void	init_ray(t_dda *dda, t_point start, t_point end)
{
	float	norm;

	dda->current_x = start.x;
	dda->current_y = start.y;
	dda->delta_x = end.x - start.x;
	dda->delta_y = end.y - start.y;
	dda->step = fmax(fabs(dda->delta_x), fabs(dda->delta_y));
	dda->x_inc = (dda->delta_x / dda->step);
	dda->y_inc = (dda->delta_y / dda->step);
	norm = sqrt(pow(dda->x_inc, 2) + pow(dda->y_inc, 2));
	dda->x_inc = dda->x_inc / norm;
	dda->y_inc = dda->y_inc / norm;
}

t_ray	cast_ray(t_session *instance, t_point start, t_point end, int color)
{
	t_dda	dda;
	t_ray	ray;
	t_point	r_pos;
	int		i;

	i = 0;
	(void)color;
	init_ray(&dda, start, end);
	while (i <= dda.step)
	{
		r_pos.y = dda.current_y;
		r_pos.x = dda.current_x;

		ray.col_point.x = dda.current_x;
		ray.col_point.y = dda.current_y;
		ray.len = i;



		if (!instance->map.grid[r_pos.y] || !instance->map.grid[r_pos.y][r_pos.x]
			|| instance->map.grid[r_pos.y][r_pos.x] == '1' || instance->map.grid[r_pos.y][r_pos.x] == ' ')
			return (ray);
		//pixel_put(&instance->mlx_img, dda.current_x, dda.current_y, color);
		

		dda.current_x += dda.x_inc;
		dda.current_y += dda.y_inc;
		i++;
	}

	return (ray);
}

// int get_colision_texture(t_session *instance)
// {
// 	if (ray.col_point.x + 1 == 0)

// 	else if (ray.col_point.x - 1 == 0)
// }

void	raycaster(t_session *instance, int x, int y, int color)
{
	t_rcaster	*rcaster;
	t_point		end;
	int			i;

	rcaster = &instance->player.raycaster;
	rcaster->n_rays = W_WIDTH;
	rcaster->fov = 1.570;
	rcaster->len = W_WIDTH;

	rcaster->angle = (instance->player.angle * PI / 180) - (rcaster->fov / 2);

	rcaster->inc = rcaster->fov / (rcaster->n_rays);
	i = 0;
	while (i < rcaster->n_rays)
	{
		end.y = y + rcaster->len * sin(rcaster->angle);
		end.x = x + rcaster->len * cos(rcaster->angle);
		// assignments
		rcaster->rays[i] =  cast_ray(instance, (t_point){x, y}, end, color);
		rcaster->rays[i].angle = rcaster->angle;

		//increments
		rcaster->angle += rcaster->inc;
		i++;
	}
}

void render3D(t_session *instance)
{
	t_ray	*rays;
	int		cam_z; // cam height

	float	cam_p; // camera plane
	float	real_d; // corrected distance


	float	wall_h; // wall height
	int		wall_t; // wall top point
	int		wall_b; // wall bot point

	rays = instance->player.raycaster.rays;

	cam_z = (W_HEIGHT / 2);
	cam_p = (W_WIDTH / 2) / tan((instance->player.raycaster.fov / 2));

	for (int i = 0; i < instance->player.raycaster.n_rays; i++)
	{

		real_d = rays[i].len * cos(instance->player.raycaster.angle * PI / 180);

		wall_h = (MAP_SCALE / real_d) * cam_p;
		wall_t = cam_z - (wall_h / 2);
		wall_b = cam_z + (wall_h / 2);
		wall_t = fmax(0, wall_t);
		wall_b = fmin(W_HEIGHT, wall_b);

		draw_line(instance, (t_point){i, wall_t},(t_point){i, wall_b}, 0xFFFFFF);
	}
}

void	update_player(t_session *instance, int x, int y)
{
	// t_point	pos;
	// int		sq;

	// sq = MAP_SCALE / 4;
	// pos.y = y - (sq / 2);
	// pos.x = x - (sq / 2);
	// draw_square(instance, pos, sq, 0x6c71c4);
	// draw_face(instance, x, y, 0x250AAA);
	raycaster(instance, x, y, 0x6c71c4);
	render3D(instance);
	for (int i = 0; i < instance->player.raycaster.n_rays; i++)
	{
		printf("coll point: x: %d y: %d\n",
			instance->player.raycaster.rays[i].col_point.x, instance->player.raycaster.rays[i].col_point.y);
		printf("ray lenght: %d\n", instance->player.raycaster.rays[i].len);
		printf("exit angle: %f\n", instance->player.raycaster.rays[i].angle);
	}
}
