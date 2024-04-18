#include "../../includes/headers/cub3d.h"

void fill_square(t_session *instance, t_point point, int sq, int color)
{
	int x, y;
	for (y = point.y; y < point.y + sq; y++)
	{
		for (x = point.x; x < point.x + sq; x++)
		{
			pixel_put(&(instance->mlx_img), x, y, color); // Assuming pixel_put function exists
		}
	}
}

void	vp_player(t_session *instance, int x, int y)
{
	t_point	pos;
	int		sq;

	sq = MAP_SCALE / 4;
	pos.y = y - (sq / 2);
	pos.x = x - (sq / 2);
	fill_square(instance, pos, sq, 0x000000); // temp player representation
	draw_square(instance, pos, sq, 0xffffff); // temp player representation
	draw_face(instance, x, y, 0xffffff); // representation of player facing dir
}

void	init_camera2d(t_session *instance, t_camera2d *cam2d)
{
	cam2d->size.x = MAP_SCALE * 5;
	cam2d->size.y = MAP_SCALE * 5;
	cam2d->p_pos.x = instance->player.x;
	cam2d->p_pos.y = instance->player.y;
	cam2d->top_l.x = fmax(0, instance->player.x - cam2d->size.x / 2);
	cam2d->top_l.y = fmax(0, instance->player.y - cam2d->size.y / 2);
	cam2d->bot_r.x = fmin(W_WIDTH - 1, instance->player.x + cam2d->size.x / 2);
	cam2d->bot_r.y = fmin(W_HEIGHT - 1, instance->player.y + cam2d->size.y / 2);
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
		cam2d.offset.y = (y - cam2d.top_l.y) + (MAP_SCALE * 3.5  - (instance->player.y - cam2d.top_l.y));
		x = cam2d.top_l.x;
		while (x < cam2d.bot_r.x && instance->map.grid[y][x])
		{
			cam2d.offset.x = (x - cam2d.top_l.x) + (MAP_SCALE * 3.5 - (instance->player.x - cam2d.top_l.x));
			//pixel_put(&(instance->mlx_img), cam2d.offset.x, cam2d.offset.y, 0x004500);
			if (instance->map.grid[y][x] == '1')
				pixel_put(&(instance->mlx_img), cam2d.offset.x, cam2d.offset.y, 0xff4500);
			else if (instance->map.grid[y][x] == '0')
				pixel_put(&(instance->mlx_img), cam2d.offset.x, cam2d.offset.y, 0xffffff);
			x++;
		}
		y++;
	}

	vp_player(instance, MAP_SCALE * 3.5, MAP_SCALE * 3.5);
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
		cam2d.offset.y = (y - cam2d.top_l.y) + (MAP_SCALE * 3.5  - (instance->player.y - cam2d.top_l.y));
		x = fmax(0, (cam2d.top_l.x - MAP_SCALE));
		while (x < cam2d.bot_r.x && instance->map.grid[y][x])
		{
			cam2d.offset.x = (x - cam2d.top_l.x) + (MAP_SCALE * 3.5 - (instance->player.x - cam2d.top_l.x));
			if (instance->map.grid[y][x] == '1' && (x % MAP_SCALE == 0 && y % MAP_SCALE == 0))
			{
				fill_square(instance, cam2d.offset, MAP_SCALE, 0xff4500 / 2);
				draw_square(instance, cam2d.offset, MAP_SCALE, 0x000000);
			}
			x++;
		}
		y++;
	}
	vp_player(instance, MAP_SCALE * 3.5, MAP_SCALE * 3.5);
}


