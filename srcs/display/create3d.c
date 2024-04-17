#include "../../includes/headers/cub3d.h"
# define TEST_COLOR 0x008000
void draw_line_t(t_session *instance, t_point start, t_point end)
{
	int	x;
	int	y;

	x = start.x;
	y = start.y;
	while (y < end.y)
	{
		pixel_put(&instance->mlx_img, x, y, TEST_COLOR);
		y++;
	}
}

int	distance_to_camera_plane(t_ray ray)
{
	return (ray.len * cos(ray.angle * PI / 180));
}

void	cast_3d(t_session *instance)
{
	int	x;
	int	y;
	int	lineHeight;
	int temp_len;
	x = -1;
	ft_printf("cast_3d\n");
	while (++x != instance->width)
	{
		temp_len = distance_to_camera_plane(instance->player.raycaster.rays[x]);
		lineHeight = (int)(instance->height / temp_len);
		y = (instance->height - lineHeight) / 2;
		draw_line_t(instance, (t_point){x, y}, (t_point){x, y + lineHeight});
	}
}
