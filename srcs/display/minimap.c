#include "../../includes/headers/cub3d.h"

void	init_camera2d(t_session *instance, t_camera2d *cam2d)
{
	cam2d->size.x = instance->width / 5;
	cam2d->size.y = instance->height / 5;
	cam2d->p_pos.x = instance->player.x;
	cam2d->p_pos.y = instance->player.y;
	cam2d->top_l.x = fmax(0, instance->player.x - cam2d->size.x / 2);
	cam2d->top_l.y = fmax(0, instance->player.y - cam2d->size.y / 2);
	cam2d->bot_r.x = fmin(instance->map.grid_w, instance->player.x + cam2d->size.x / 2);
	cam2d->bot_r.y = fmin(instance->map.grid_h, instance->player.y + cam2d->size.y / 2);
}

void	vp_player(t_session *instance, int x, int y)
{
	t_point	pos;
	int		sq;

	sq = 16;
	pos.y = y - (sq / 2);
	pos.x = x - (sq / 2);
	fill_square(instance, pos, sq, 0x000000);
	draw_square(instance, pos, sq, 0xffffff);
	draw_face(instance, x, y, 0xff4500);
}

# define H_SCALE instance->height / 7
# define W_SCALE instance->width / 8

void vp_scaled(t_session *instance)
{
	int			y;
	int			x;
	int			color;
	t_camera2d	cam2d;

	if (instance->mode.type == PLAY && instance->mode.sub != MINIMAP)
		return ;
	init_camera2d(instance, &cam2d);
	y = cam2d.top_l.y;
	while (y < cam2d.bot_r.y && instance->map.grid[y])
	{
		cam2d.offset.y = (y - cam2d.top_l.y) + (H_SCALE  - (instance->player.y - cam2d.top_l.y));
		x = cam2d.top_l.x;
		while (x < cam2d.bot_r.x && instance->map.grid[y][x])
		{
			cam2d.offset.x = (x - cam2d.top_l.x) + (W_SCALE - (instance->player.x - cam2d.top_l.x));
			color = get_pixel(&instance->mlx_img, cam2d.offset.x, cam2d.offset.y);
			if (instance->map.grid[y][x] == '1')
				pixel_put(instance, cam2d.offset.x, cam2d.offset.y, color + 0xf0f010);
			else if (instance->map.grid[y][x] == '0')
				pixel_put(instance, cam2d.offset.x, cam2d.offset.y, color + 0x004550);
			x++;
		}
		y++;
	}
	vp_player(instance, W_SCALE, H_SCALE);
}


// void vp_grid(t_session *instance)
// {
// 	int			y;
// 	int			x;
// 	t_camera2d	cam2d;

// 	init_camera2d(instance, &cam2d);
// 	y = fmax(0, (cam2d.top_l.y - MAP_SCALE));
// 	while (y < cam2d.bot_r.y && instance->map.grid[y])
// 	{
// 		cam2d.offset.y = (y - cam2d.top_l.y) + (MAP_SCALE * 3.5  - (instance->player.y - cam2d.top_l.y));
// 		x = fmax(0, (cam2d.top_l.x - MAP_SCALE));
// 		while (x < cam2d.bot_r.x && instance->map.grid[y][x])
// 		{
// 			cam2d.offset.x = (x - cam2d.top_l.x) + (MAP_SCALE * 3.5 - (instance->player.x - cam2d.top_l.x));
// 			if (instance->map.grid[y][x] == '1' && (x % MAP_SCALE == 0 && y % MAP_SCALE == 0))
// 			{
// 				fill_square(instance, cam2d.offset, MAP_SCALE, 0xff4500 / 2);
// 				draw_square(instance, cam2d.offset, MAP_SCALE, 0x000000);
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// 	vp_player(instance, MAP_SCALE * 3.5, MAP_SCALE * 3.5);
// }


