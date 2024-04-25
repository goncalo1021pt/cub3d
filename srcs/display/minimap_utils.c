
#include "../../includes/headers/cub3d.h"

int	split_size(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

size_t	max_len(char **split)
{
	int		i;
	size_t	max;

	i = 0;
	max = 0;
	while (split[i])
	{
		if (ft_strlen(split[i]) > max)
			max = ft_strlen(split[i]);
		i++;
	}
	return (max);
}

void fill_square(t_session *instance, t_point point, int sq, int color)
{
	int	x;
	int	y;
	y = point.y;
	while (y < point.y + sq)
	{
		x = point.x;
		while ( x < point.x + sq)
		{
			pixel_put(instance, x, y, color);
			x++;
		}
		y++;
	}
}
/* draw square faces counter clockwise start tih the top border */
void	draw_square(t_session *instance, t_point point, int sq, int color)
{
	t_point	start;
	t_point end;

	start = point;
	end.x = point.x + sq;
	end.y = point.y;
	draw_line(instance, start, end, color);
	end.x = point.x;
	end.y = point.y + sq;
	draw_line(instance, start, end, color);
	start.x = point.x;
	start.y = point.y + sq;
	end.x = point.x + sq;
	end.y = point.y + sq;
	draw_line(instance, start, end, color);
	start.x = point.x + sq;
	start.y = point.y;
	end.x = point.x + sq;
	end.y = point.y + sq;
	draw_line(instance, start, end, color);
}

void	draw_face(t_session *instance, int x, int y, int color)
{
	int		length;
	t_point	end;

	length = 16;
	end.y = y + length * sin(instance->player.angle * PI / 180);
	end.x = x + length * cos(instance->player.angle * PI / 180);
	draw_line(instance, (t_point){x, y}, end, color);
}
