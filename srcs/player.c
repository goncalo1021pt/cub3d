#include "../includes/headers/cub3d.h"

void	cast_ray(t_session *instance, t_point start, t_point end, int color)
{
	t_dda	dda;
	t_point	r_pos;
	int		i;

	i = 0;
	init_dda(&dda, start, end);
	while (i <= dda.step)
	{
		r_pos.y = dda.current_y;
		r_pos.x = dda.current_x;
		if (!instance->map.grid[r_pos.y] || !instance->map.grid[r_pos.y][r_pos.x] || instance->map.grid[r_pos.y][r_pos.x] == '1' || instance->map.grid[r_pos.y][r_pos.x] == ' ')
			return;
		pixel_put(&instance->mlx_img, dda.current_x, dda.current_y, color);
		dda.current_x += dda.x_inc;
		dda.current_y += dda.y_inc;
		i++;
	}
}

typedef struct s_rcaster
{
	float	fov;
	float	angle;
	float 	inc;
	int		len;
	int		n_rays;
} t_rcaster;

void	raycaster(t_session *instance, int x, int y, int color)
{
	t_rcaster	rcaster;
	t_point		end;
	int			i;

	rcaster.n_rays = W_WIDTH;
	rcaster.fov = 80;
	rcaster.len = W_WIDTH;
	rcaster.angle = instance->player.angle - (rcaster.fov / 2);
	rcaster.inc = rcaster.fov / (rcaster.n_rays);
	i = 0;
	while (i < rcaster.n_rays)
	{
		end.y = y + rcaster.len * sin(rcaster.angle * PI / 180);
		end.x = x + rcaster.len * cos(rcaster.angle * PI / 180);
		cast_ray(instance, (t_point){x, y}, end, color);
		rcaster.angle += rcaster.inc;
		i++;
	}
}

void	update_player(t_session *instance, int x, int y)
{
	t_point	pos;
	int		sq;

	sq = MAP_SCALE / 4;
	pos.y = y - (sq / 2);
	pos.x = x - (sq / 2);
	draw_square(instance, pos, sq, 0x6c71c4);
	raycaster(instance, x, y, 0x6c71c4);
	draw_face(instance, x, y, 0x250AAA);
}
