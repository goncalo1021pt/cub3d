#include "../includes/headers/cub3d.h"

t_ray	cast_ray(t_session *instance, t_point start, t_point end, int color)
{
	t_dda	dda;
	t_ray	ray;
	t_point	r_pos;
	int		i;

	i = 0;
	(void)color;
	init_dda(&dda, start, end);
	while (i <= dda.step)
	{
		r_pos.y = dda.current_y;
		r_pos.x = dda.current_x;
		//
		ray.col_point.x = dda.current_x;
		ray.col_point.y = dda.current_y;
		ray.len = i;
		if (ray.col_point.x < 0 || ray.col_point.x > W_WIDTH) //clamp rays ?
			ray.col_point.x = W_WIDTH;
		if (ray.col_point.y < 0 || ray.col_point.y > W_WIDTH)
			ray.col_point.y = W_WIDTH;	
		//
		if (!instance->map.grid[r_pos.y] || !instance->map.grid[r_pos.y][r_pos.x]
			|| instance->map.grid[r_pos.y][r_pos.x] == '1' || instance->map.grid[r_pos.y][r_pos.x] == ' ')
			return (ray);
		//pixel_put(&instance->mlx_img, dda.current_x, dda.current_y, color);
		dda.current_x += dda.x_inc;
		dda.current_y += dda.y_inc;
		i++;
	}
	//ray.col_point.x = dda.current_x;
	//ray.col_point.y = dda.current_y;
	//ray.len = i;
	return (ray);
}

void	raycaster(t_session *instance, int x, int y, int color)
{
	t_rcaster	*rcaster;
	t_point		end;
	int			i;

	rcaster = &instance->player.raycaster;
	rcaster->n_rays = W_WIDTH;
	rcaster->fov = 80;
	rcaster->len = W_WIDTH;
	rcaster->angle = instance->player.angle - (rcaster->fov / 2);
	rcaster->inc = rcaster->fov / (rcaster->n_rays);
	i = 0;
	while (i < rcaster->n_rays)
	{
		end.y = y + rcaster->len * sin(rcaster->angle * PI / 180);
		end.x = x + rcaster->len * cos(rcaster->angle * PI / 180);
		//
		rcaster->rays[i] =  cast_ray(instance, (t_point){x, y}, end, color);
		rcaster->rays[i].angle = rcaster->angle;
		//
		rcaster->angle += rcaster->inc;
		i++;
	}
}

void render3D(t_session *instance)
{
	t_ray	*rays;
	int		cam_z; // cam height
	float	cam_d; // cam distance
	float	real_d; // corrected distance
	float	a_diff; // angle difference rom ray angle to cam
	float	wall_h; // wall height
	int		wall_t; // wall top point
	int		wall_b; // wall bot point
	
	rays = instance->player.raycaster.rays;

	cam_z = (W_HEIGHT / 2);
	cam_d = (W_WIDTH / 2) / tan((instance->player.raycaster.fov / 2) * (PI / 180));
	
	for (int i = 0; i < instance->player.raycaster.n_rays; i++)
	{
		a_diff = (rays[i].angle - instance->player.angle) * (PI / 180);
		a_diff = fmod(a_diff + PI, 2 * PI) - PI;
		real_d = rays[i].len * cos(a_diff);

		wall_h = (MAP_SCALE / real_d) * cam_d;
		wall_t = cam_z - (wall_h / 2);
		wall_b = cam_z + (wall_h / 2);
		wall_t = fmax(0, wall_t);
		wall_b = fmin(W_HEIGHT, wall_b);
		
		draw_line(instance, (t_point){i, wall_t},(t_point){i, wall_b}, 0xFFFFFF);
	}
}

void	update_player(t_session *instance, int x, int y)
{
	t_point	pos;
	int		sq;

	sq = MAP_SCALE / 4;
	pos.y = y - (sq / 2);
	pos.x = x - (sq / 2);
	//draw_square(instance, pos, sq, 0x6c71c4);
	raycaster(instance, x, y, 0x6c71c4);
	render3D(instance);
	// for (int i = 0; i < instance->player.raycaster.n_rays; i++)
	// {
	// 	printf("coll point: x: %d y: %d\n",
	// 		instance->player.raycaster.rays[i].col_point.x, instance->player.raycaster.rays[i].col_point.y);
	// 	printf("ray lenght: %d\n", instance->player.raycaster.rays[i].len);
	// 	printf("exit angle: %f\n", instance->player.raycaster.rays[i].angle);
	// }
	//draw_face(instance, x, y, 0x250AAA);
}
