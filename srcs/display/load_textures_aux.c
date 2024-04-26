#include "../../includes/headers/cub3d.h"

void	read_textures_2(t_session *ist)
{
	ist->textures[DOOR_TEXTURE_1].img = mlx_xpm_file_to_image(ist->mlx_ser,
			"./includes/assets/door_1.xpm", &ist->textures[DOOR_TEXTURE_1].width,
			&ist->textures[DOOR_TEXTURE_1].height);
	ist->textures[DOOR_TEXTURE_2].img = mlx_xpm_file_to_image(ist->mlx_ser,
			"./includes/assets/door_2.xpm", &ist->textures[DOOR_TEXTURE_2].width,
			&ist->textures[DOOR_TEXTURE_2].height);
	ist->textures[DOOR_TEXTURE_3].img = mlx_xpm_file_to_image(ist->mlx_ser,
			"./includes/assets/door_3.xpm", &ist->textures[DOOR_TEXTURE_3].width,
			&ist->textures[DOOR_TEXTURE_3].height);
	ist->textures[DOOR_TEXTURE_4].img = mlx_xpm_file_to_image(ist->mlx_ser,
			"./includes/assets/door_4.xpm", &ist->textures[DOOR_TEXTURE_4].width,
			&ist->textures[DOOR_TEXTURE_4].height);
	ist->textures[DOOR_TEXTURE_5].img = mlx_xpm_file_to_image(ist->mlx_ser,
			"./includes/assets/door_5.xpm", &ist->textures[DOOR_TEXTURE_5].width,
			&ist->textures[DOOR_TEXTURE_5].height);
}

void	read_textures(t_session *ist)
{
	ist->textures[NORTH_TEXTURE].img = mlx_xpm_file_to_image(ist->mlx_ser,
			ist->map.no, &ist->textures[NORTH_TEXTURE].width,
			&ist->textures[NORTH_TEXTURE].height);
	ist->textures[SOUTH_TEXTURE].img = mlx_xpm_file_to_image(ist->mlx_ser,
			ist->map.so, &ist->textures[SOUTH_TEXTURE].width,
			&ist->textures[SOUTH_TEXTURE].height);
	ist->textures[WEST_TEXTURE].img = mlx_xpm_file_to_image(ist->mlx_ser,
			ist->map.we, &ist->textures[WEST_TEXTURE].width,
			&ist->textures[WEST_TEXTURE].height);
	ist->textures[EAST_TEXTURE].img = mlx_xpm_file_to_image(ist->mlx_ser,
			ist->map.ea, &ist->textures[EAST_TEXTURE].width,
			&ist->textures[EAST_TEXTURE].height);
	read_textures_2(ist);
}

void	get_tex_data_3(t_session *ist)
{
	ist->textures[DOOR_TEXTURE_4].addr
		= mlx_get_data_addr(ist->textures[DOOR_TEXTURE_4].img,
			&ist->textures[DOOR_TEXTURE_4].bpp,
			&ist->textures[DOOR_TEXTURE_4].line_length,
			&ist->textures[DOOR_TEXTURE_4].endian);
	ist->textures[DOOR_TEXTURE_5].addr
		= mlx_get_data_addr(ist->textures[DOOR_TEXTURE_5].img,
			&ist->textures[DOOR_TEXTURE_5].bpp,
			&ist->textures[DOOR_TEXTURE_5].line_length,
			&ist->textures[DOOR_TEXTURE_5].endian);
}

void	get_tex_data_2(t_session *ist)
{
	ist->textures[DOOR_TEXTURE_1].addr
		= mlx_get_data_addr(ist->textures[DOOR_TEXTURE_1].img,
			&ist->textures[DOOR_TEXTURE_1].bpp,
			&ist->textures[DOOR_TEXTURE_1].line_length,
			&ist->textures[DOOR_TEXTURE_1].endian);
	ist->textures[DOOR_TEXTURE_2].addr
		= mlx_get_data_addr(ist->textures[DOOR_TEXTURE_2].img,
			&ist->textures[DOOR_TEXTURE_2].bpp,
			&ist->textures[DOOR_TEXTURE_2].line_length,
			&ist->textures[DOOR_TEXTURE_2].endian);
	ist->textures[DOOR_TEXTURE_3].addr
		= mlx_get_data_addr(ist->textures[DOOR_TEXTURE_3].img,
			&ist->textures[DOOR_TEXTURE_3].bpp,
			&ist->textures[DOOR_TEXTURE_3].line_length,
			&ist->textures[DOOR_TEXTURE_3].endian);
}

void	get_tex_data_1(t_session *ist)
{
	ist->textures[NORTH_TEXTURE].addr
		= mlx_get_data_addr(ist->textures[NORTH_TEXTURE].img,
			&ist->textures[NORTH_TEXTURE].bpp,
			&ist->textures[NORTH_TEXTURE].line_length,
			&ist->textures[NORTH_TEXTURE].endian);
	ist->textures[SOUTH_TEXTURE].addr
		= mlx_get_data_addr(ist->textures[SOUTH_TEXTURE].img,
			&ist->textures[SOUTH_TEXTURE].bpp,
			&ist->textures[SOUTH_TEXTURE].line_length,
			&ist->textures[SOUTH_TEXTURE].endian);
	ist->textures[WEST_TEXTURE].addr
		= mlx_get_data_addr(ist->textures[WEST_TEXTURE].img,
			&ist->textures[WEST_TEXTURE].bpp,
			&ist->textures[WEST_TEXTURE].line_length,
			&ist->textures[WEST_TEXTURE].endian);
	ist->textures[EAST_TEXTURE].addr
		= mlx_get_data_addr(ist->textures[EAST_TEXTURE].img,
			&ist->textures[EAST_TEXTURE].bpp,
			&ist->textures[EAST_TEXTURE].line_length,
			&ist->textures[EAST_TEXTURE].endian);
	get_tex_data_2(ist);
	get_tex_data_3(ist);
	ist->textures[DOOR_TEXTURE] = ist->textures[DOOR_TEXTURE_1];
}
