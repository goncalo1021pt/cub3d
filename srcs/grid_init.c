#include "../includes/headers/cub3d.h"

int	get_max_len(t_map *map)
{
	int	ctd;
	int	max_len;

	ctd = 0;
	max_len = 0;
	while (map->buffer[ctd])
	{
		if (max_len < (int)ft_strlen(map->buffer[ctd]))
			max_len = ft_strlen(map->buffer[ctd]);
		ctd++;
	}
	return (max_len);
}

void	free_prev(char **arr_str, int ctd)
{
	while (ctd >= 0)
	{
		free(arr_str[ctd]);
		ctd--;
	}
	free(arr_str);
}

void	scale_grid(t_map *map, int x, int y)
{
	int	ctd;
	int	ctd2;

	ctd = 0;
	while (ctd < MAP_SCALE)
	{
		ctd2 = 0;
		while (ctd2 < MAP_SCALE)
		{
			if (is_in_array(PLAYER, map->map[x][y]))
				map->grid[(x * MAP_SCALE) + ctd][(y * MAP_SCALE) + ctd2] = '0';
			else
				map->grid[(x * MAP_SCALE) + ctd][(y * MAP_SCALE)
					+ ctd2] = map->map[x][y];
			ctd2++;
		}
		ctd++;
	}
	if (is_in_array(PLAYER, map->map[x][y]))
		map->grid[(x * MAP_SCALE) + (MAP_SCALE / 2)][(y * MAP_SCALE) + (MAP_SCALE / 2)] = map->map[x][y];
}

void	set_grid(t_map *map)
{
	int	ctd;
	int	ctd2;

	ctd = 0;
	while (map->map[ctd])
	{
		ctd2 = 0;
		while (map->map[ctd][ctd2])
		{
			scale_grid(map, ctd, ctd2);
			ctd2++;
		}
		ctd++;
	}
}

bool	create_grid(t_map *map)
{
	int	ctd;
	int	rows;

	ctd = 0;
	rows = ft_strslen(map->map);
	map->grid = (char **)ft_calloc(sizeof(char *), (rows * MAP_SCALE) + 1);
	if (!map->grid)
		return (ft_putendl_fd(ERR_ALLOC, 2), false);
	while (ctd < rows * MAP_SCALE)
	{
		map->grid[ctd] = (char *)ft_calloc(sizeof(char), (ft_strlen(map->map[ctd
						/ MAP_SCALE]) * MAP_SCALE) + 1);
		if (!map->grid[ctd])
			return (free_prev(map->grid, ctd - 1), ft_putendl_fd(ERR_ALLOC, 2),
				false);
		ctd++;
	}
	set_grid(map);
	return (true);
}
