#include "../../includes/headers/cub3d.h"

void init_array(t_session *instance)
{
	instance->textures[NORT_TEXTURE].img = NULL;
	instance->textures[SOUTH_TEXTURE].img = NULL;
	instance->textures[WEST_TEXTURE].img = NULL;
	instance->textures[EAST_TEXTURE].img = NULL;
	instance->textures[CEALING_TEXTURE].img = NULL;
	instance->textures[FLOOR_TEXTURE].img = NULL;
}

void destroy_textures(t_session *instance)
{
	int i;

	i = 0;
	while (i < 6)
	{
		if (instance->textures[i].img)
			mlx_destroy_image(instance->mlx_ser, instance->textures[i].img);
		i++;
	}
}

bool mlx_vars_init(t_session *instance)
{
	instance->width = W_WIDTH;
	instance->height = W_HEIGHT;
	instance->mlx_ser = mlx_init();
	init_array(instance);
	// mlx_get_screen_size(instance->mlx_ser, &instance->width, &instance->height);
	instance->mlx_win = mlx_new_window(instance->mlx_ser, instance->width, instance->height, "cub3d");	
	// mlx_mouse_hide(instance->mlx_ser, instance->mlx_win);
	instance->mlx_img.img = mlx_new_image(instance->mlx_ser, instance->width, instance->height);
	instance->mlx_img.addr = mlx_get_data_addr(instance->mlx_img.img,
			&instance->mlx_img.bpp, &instance->mlx_img.line_length,
			&instance->mlx_img.endian);
	if (!load_textures(instance))
		return (false);
	return (true);
}
