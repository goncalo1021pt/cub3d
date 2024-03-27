#include "../includes/headers/cub3d.h"

bool	check_loaded_textures(t_map *map)
{
	if (map->no == NULL || map->so == NULL || map->we == NULL
		|| map->ea == NULL)
		return (false);
	return (true);
}

char	*clean_texture(char *line)
{
	int		new_len;
	char	*new_line;
	int		ctd;
	int		ctd2;

	new_len = 0;
	ctd = -1;
	while (line[++ctd])
	{
		if (line[ctd] && (((ctd == 0 && line[ctd] != ' ') || (line[ctd] != ' '
						|| (line[ctd] == ' ' && line[ctd - 1] != ' ')))))
			new_len++;
	}
	new_line = ft_calloc(new_len + 1, sizeof(char));
	if (!new_line)
		return (NULL);
	ctd = -1;
	ctd2 = -1;
	while (line[++ctd])
	{
		if (line[ctd] && (((ctd == 0 && line[ctd] != ' ') || (line[ctd] != ' '
						|| (line[ctd] == ' ' && line[ctd - 1] != ' ')))))
			new_line[++ctd2] = line[ctd];
	}
	return (new_line);
}

bool	set_texture(char *line, t_map *map)
{
	if (map->no == NULL && ft_strncmp(line, "NO ", 3) == 0)
	{
		map->no = ft_strtrim(line + 3, " ");
		ft_printf("NO: %s\n", map->no);
		return (true);
	}
	if (map->so == NULL && ft_strncmp(line, "SO ", 3) == 0)
	{
		map->so = ft_strtrim(line + 3, " ");
		ft_printf("SO: %s\n", map->so);
		return (true);
	}
	if (map->we == NULL && ft_strncmp(line, "WE ", 3) == 0)
	{
		map->we = ft_strtrim(line + 3, " ");
		ft_printf("WE: %s\n", map->we);
		return (true);
	}
	if (map->ea == NULL && ft_strncmp(line, "EA ", 3) == 0)
	{
		map->ea = ft_strtrim(line + 3, " ");
		ft_printf("EA: %s\n", map->ea);
		return (true);
	}
	return (false);
}

char	*tabs_to_spaces(char *line)
{
	int		ctd;

	ctd = -1;
	while (line[++ctd])
	{
		if (line[ctd] == '\t')
			line[ctd] = ' ';
	}
	return (line);
}

bool	get_textures(t_map *map)
{
	char	*line;
	int		ctd;

	ctd = 0;
	while (!check_loaded_textures(map))
	{
		if (!map->buffer[ctd])
			return (ft_putendl_fd(ERR_TEXTURE, 2), false);
		line = clean_texture(tabs_to_spaces(map->buffer[ctd]));
		if (!line)
			return (ft_putendl_fd(ERR_TEXTURE, 2), false);
		if (line[0] && !set_texture(line, map))
			return (free(line), ft_putendl_fd(ERR_TEXTURE, 2), false);
		free(line);
		ctd++;
	}
	return (true);
}
