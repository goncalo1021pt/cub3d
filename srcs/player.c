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
		if (!instance->map.grid[r_pos.y] || !instance->map.grid[r_pos.y][r_pos.x] || instance->map.grid[r_pos.y][r_pos.x] == '1')
			return;
		pixel_put(&instance->mlx_img, dda.current_x, dda.current_y, color);
		dda.current_x += dda.x_inc;
		dda.current_y += dda.y_inc;
		i++;
	}
}

void draw_face(t_session *instance, int x, int y, int color)
{
	int		length;
	t_point	end;

	length = MAP_SCALE / 4;
	end.y = y + length * sin(instance->player.angle * PI / 180);
	end.x = x + length * cos(instance->player.angle * PI / 180);
	draw_line(instance, (t_point){x, y}, end, color);
}

typedef struct s_rcaster
{
	float	fov;
	float	angle;
	float 	inc;
	int		len;
	int		n_rays;
} t_rcaster;

int	is_in_bounds(t_point start, t_point end)
{
	if (start.x < 0 || start.y < 0 || start.x > W_WIDTH || start.y > W_HEIGHT)
		return (0);
	else if (end.x < 0 || end.y < 0 || end.x > W_WIDTH || end.y > W_HEIGHT)
		return (0);	
	else
		return(1);
}

void	raycaster(t_session *instance, int x, int y, int color)
{
	t_rcaster	rcaster;
	t_point		end;
	int			i;

	rcaster.n_rays = W_WIDTH;
	rcaster.fov = 80.0;
	rcaster.len = W_WIDTH;
	rcaster.angle = instance->player.angle - (rcaster.fov / 2);
	rcaster.inc = rcaster.fov / (rcaster.n_rays - 1);
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

void	draw_player(t_session *instance, int x, int y)
{
	t_point	pos;
	int		sq;

	sq = MAP_SCALE / 4;
	pos.y = y - (sq / 2);
	pos.x = x - (sq / 2);
	draw_square(instance, pos, sq, 0x6c71c4); // temp player representation
	raycaster(instance, x, y, 0x6c71c4); // casts rays from player pos into player dir
	draw_face(instance, x, y, 0x250AAA); // representation of player facing dir
}