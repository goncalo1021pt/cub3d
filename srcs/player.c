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

double formula(t_ray ray)
{
	float aux;

	aux = ray.len * cos((ray.angle));
	return (roundf(aux));
}

t_ray	cast_ray(t_session *instance, t_point start, t_point end, int color)
{
	t_dda	dda;
	t_ray	ray;
	t_point	r_pos;
	float		i;

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

		dda.current_x += dda.x_inc * 0.1;
		dda.current_y += dda.y_inc * 0.1;
		i+= 0.1;
	}

	return (ray);
}
void	raycaster(t_session *instance, int x, int y, int color)
{
	t_rcaster	*caster;
	t_point		end;
	int			i;

	caster = &instance->player.raycaster;
	caster->n_rays =  W_WIDTH;
	caster->fov = 1.221; //1.570;
	caster->len = W_WIDTH;

	caster->angle = (instance->player.angle * (PI / 180)) - (caster->fov / 2);

	caster->inc = caster->fov / (caster->n_rays);
	i = 0;
	while (i < caster->n_rays)
	{
		end.y = y + truncf(caster->len * sin(caster->angle));
		end.x = x + truncf(caster->len * cos(caster->angle));

		// assignments
		printf("caster angle in raycaster: %f\n", caster->angle);
		caster->rays[i] =  cast_ray(instance, (t_point){x, y}, end, color);
		caster->rays[i].angle = -(caster->fov / 2) + i * (caster->fov / (caster->n_rays - 1));
		caster->rays[i].len = formula(caster->rays[i]);

		//increments

		caster->angle += caster->inc;
		i++;
	}
}

void render3D(t_session *instance)
{
	t_ray	*rays;
	t_rcaster	*caster;

	int		cam_z; // cam height
	float	cam_p; // camera plane
	float	real_d;
	int		wall_h; // wall height
	int		wall_t; // wall top point
	int		wall_b; // wall bot point

	caster = &instance->player.raycaster;
	rays = caster->rays;
	cam_z = (W_HEIGHT / 2);
	cam_p = (W_WIDTH / 2) / tan((caster->fov / 2));

	for (int i = 0; i < instance->player.raycaster.n_rays; i++)
	{

		if (rays[i].len > 0)
		{
			printf("caster angle in renderer: %f\n", caster->angle);
			real_d = fabs(rays[i].len * cos(caster->angle * (PI / 180))); // this is unecessary real_d is 35.996 instead of 36.0 in rays[i].len
			wall_h = (MAP_SCALE / real_d) * cam_p;
			wall_t = cam_z - (wall_h / 2);
			wall_b = cam_z + (wall_h / 2);
			wall_t = fmax(0, wall_t);
			wall_b = fmin(W_HEIGHT, wall_b);
			draw_line(instance, (t_point){i, wall_t},(t_point){i, wall_b}, 0xFFFFFF / 2);
		}

		printf("rays[%d].len: %f | real_d: %f | ray angle: %f\n", i, rays[i].len, real_d, rays[i].angle);
	}
}

void	update_player(t_session *instance, int x, int y)
{
	raycaster(instance, x, y, 0x6c71c4);
	render3D(instance);
}
