#include "../includes/headers/cub3d.h"

bool	check_name(char *name)
{
	int	len;

	len = ft_strlen(name);
	name = name + len - 4;
	if (len < 4 && !ft_strncmp(name, ".cub", 4))
		return (ft_putendl_fd(INVALID_MAPNAME, 2), false);
	return (true);
}

bool	read_map(t_map *map, int fd, int loopn)
{
	char	*line;

	line = get_next_line(fd);
	if (line)
	{
		if (!read_map(map, fd, loopn + 1))
			return (false);
	}
	else
	{
		map->map = ft_calloc((loopn + 1), sizeof(char *));
		if (!map->map)
			return (false);
	}
	if (map->map != NULL)
	{
		map->map[loopn] = line;
		return (true);
	}
	return (false);
}

bool	get_map(char *name, t_map *map)
{
	int	fd;

	fd = open(name, O_RDONLY);
	if (fd < 0)
		return (false);
	if (!read_map(map, fd, 0))
		return (close(fd), false);
	close(fd);
	return (true);
}

bool	parser(int argc, char **argv, t_map *map)
{
	if (argc != 2)
		return (false);
	if (!check_name(argv[1]))
		return (false);
	if (!get_map(argv[1], map))
		return (false);
	if (!validate_map(map))
		return (false);
	return (true);
}
