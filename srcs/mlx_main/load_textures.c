#include "../../includes/headers/cub3d.h"

bool load_textures(t_session *ist)
{
	ist->textures[NORT_TEXTURE].img = mlx_xpm_file_to_image(ist->mlx_ser, ist->map.no,&ist->textures[NORT_TEXTURE].width, &ist->textures[NORT_TEXTURE].height);
	ist->textures[SOUTH_TEXTURE].img = mlx_xpm_file_to_image(ist->mlx_ser, ist->map.so,&ist->textures[SOUTH_TEXTURE].width, &ist->textures[SOUTH_TEXTURE].height);
	ist->textures[WEST_TEXTURE].img = mlx_xpm_file_to_image(ist->mlx_ser, ist->map.we,&ist->textures[WEST_TEXTURE].width, &ist->textures[WEST_TEXTURE].height);
	ist->textures[EAST_TEXTURE].img = mlx_xpm_file_to_image(ist->mlx_ser, ist->map.ea,&ist->textures[EAST_TEXTURE].width, &ist->textures[EAST_TEXTURE].height);
	if (!ist->textures[NORT_TEXTURE].img || !ist->textures[SOUTH_TEXTURE].img || !ist->textures[WEST_TEXTURE].img || !ist->textures[EAST_TEXTURE].img)
		return (ft_putendl_fd(ERR_TEXTURE_LOAD, 2), false);
	ist->textures[NORT_TEXTURE].addr = mlx_get_data_addr(ist->textures[NORT_TEXTURE].img, &ist->textures[NORT_TEXTURE].bpp, &ist->textures[NORT_TEXTURE].line_length, &ist->textures[NORT_TEXTURE].endian);
	ist->textures[SOUTH_TEXTURE].addr = mlx_get_data_addr(ist->textures[SOUTH_TEXTURE].img, &ist->textures[SOUTH_TEXTURE].bpp, &ist->textures[SOUTH_TEXTURE].line_length, &ist->textures[SOUTH_TEXTURE].endian);
	ist->textures[WEST_TEXTURE].addr = mlx_get_data_addr(ist->textures[WEST_TEXTURE].img, &ist->textures[WEST_TEXTURE].bpp, &ist->textures[WEST_TEXTURE].line_length, &ist->textures[WEST_TEXTURE].endian);
	ist->textures[EAST_TEXTURE].addr = mlx_get_data_addr(ist->textures[EAST_TEXTURE].img, &ist->textures[EAST_TEXTURE].bpp, &ist->textures[EAST_TEXTURE].line_length, &ist->textures[EAST_TEXTURE].endian);
	return (true);
}