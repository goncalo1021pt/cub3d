#include "../includes/headers/cub3d.h"

typedef struct s_camera2d
{
	t_point	top_l;
	t_point	bot_r;
	t_point	p_pos;
	t_point size;
	t_point offset;
}	t_camera2d;



void	vp_player(t_session *instance, int x, int y)
{
	t_point	pos;
	int		sq;

	sq = MAP_SCALE / 4;
	pos.y = y - (sq / 2);
	pos.x = x - (sq / 2);
	draw_square(instance, pos, sq, 0x6c71c4); // temp player representation
	draw_face(instance, x, y, 0x250AAA); // representation of player facing dir
}

void	init_camera2d(t_session *instance, t_camera2d *cam2d)
{
	cam2d->size.x = MAP_SCALE * 6;
	cam2d->size.y = MAP_SCALE * 6;
	cam2d->p_pos.x = instance->player.x;
	cam2d->p_pos.y = instance->player.y;
	cam2d->top_l.x = fmax(0, instance->player.x - cam2d->size.x / 2);
	cam2d->top_l.y = fmax(0, instance->player.y - cam2d->size.y / 2);
	cam2d->bot_r.x = fmin(W_WIDTH - 1, instance->player.x + cam2d->size.x / 2);
	cam2d->bot_r.y = fmin(W_HEIGHT - 1, instance->player.y + cam2d->size.y / 2);
}

void vp_grid(t_session *instance)
{
	int			y;
	int			x;
	t_camera2d	cam2d;

	init_camera2d(instance, &cam2d);
	y = fmax(0, (cam2d.top_l.y - MAP_SCALE));
	while (y < cam2d.bot_r.y && instance->map.grid[y])
	{
		cam2d.offset.y = (y - cam2d.top_l.y) + (W_HEIGHT - (MAP_SCALE * 2) - (instance->player.y - cam2d.top_l.y));
		x = fmax(0, (cam2d.top_l.x - MAP_SCALE));
		while (x < cam2d.bot_r.x && instance->map.grid[y][x])
		{
			cam2d.offset.x = (x - cam2d.top_l.x) + (W_WIDTH / 9 - (instance->player.x - cam2d.top_l.x));
			if (instance->map.grid[y][x] == '1' && (x % MAP_SCALE == 0 && y % MAP_SCALE == 0))
				draw_square(instance, ((t_point){cam2d.offset.x, cam2d.offset.y}), MAP_SCALE, 0x000000);
			x++;
		}
		y++;
	}
}


void vp_scaled(t_session *instance)
{
	int	y;
	int	x;
	t_camera2d	cam2d;

	init_camera2d(instance, &cam2d);
	y = cam2d.top_l.y;
	while (y < cam2d.bot_r.y && instance->map.grid[y])
	{
		x = cam2d.top_l.x;
		while (x < cam2d.bot_r.x && instance->map.grid[y][x])
		{
			cam2d.offset.x = (x - cam2d.top_l.x) + (W_WIDTH / 9 - (instance->player.x - cam2d.top_l.x));
			cam2d.offset.y = (y - cam2d.top_l.y) + (W_HEIGHT - (MAP_SCALE * 2) - (instance->player.y - cam2d.top_l.y));
			if (instance->map.grid[y][x] == '1')
				pixel_put(&(instance->mlx_img), cam2d.offset.x, cam2d.offset.y, 0xff4500);
			else if (instance->map.grid[y][x] == '0')
				pixel_put(&(instance->mlx_img), cam2d.offset.x, cam2d.offset.y, 0xffffff);
			x++;
		}
		y++;
	}
}
