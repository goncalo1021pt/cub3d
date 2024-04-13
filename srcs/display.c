
#include "../includes/headers/cub3d.h"

void	mlx_shutdown(t_session *instance)
{
	mlx_loop_end(instance->mlx_ser);
	if (instance->mlx_img.img)
		mlx_destroy_image(instance->mlx_ser, instance->mlx_img.img);
	if (instance->mlx_win)
	{
		mlx_destroy_window(instance->mlx_ser, instance->mlx_win);
		instance->mlx_win = NULL;
	}
	if (instance->mlx_ser)
	{
		mlx_destroy_display(instance->mlx_ser);
		free(instance->mlx_ser);
	}
	clean_parser(&instance->map);
	//free(instance); // maybe return ?
	exit(0);
}

void	mlx_update(t_session *instance)
{
	clear_image(instance, 0x000000);
	//raycast
	debug2D(instance);
	update_player(instance, instance->player.x, instance->player.y);
	//minimap
	vp_scaled(instance);
	vp_grid(instance);
	vp_player(instance, W_WIDTH / 9, W_HEIGHT - (MAP_SCALE * 2));
	//push to window
	mlx_put_image_to_window(instance->mlx_ser,
		instance->mlx_win, instance->mlx_img.img, 0, 0);
}

void	mlx_startup(t_session *instance)
{
	instance->height = 0;
	instance->width = 0;
	instance->mlx_ser = mlx_init();
	instance->mlx_win = mlx_new_window(instance->mlx_ser, W_WIDTH, W_HEIGHT, "cub3d");
	instance->width = W_WIDTH;
	instance->height = W_HEIGHT;
	instance->mlx_img.img = mlx_new_image(instance->mlx_ser, W_WIDTH, W_HEIGHT);
	instance->mlx_img.addr = mlx_get_data_addr(instance->mlx_img.img,
			&instance->mlx_img.bits_per_pixel, &instance->mlx_img.line_length,
			&instance->mlx_img.endian);
	if (!instance->mlx_ser || !instance->mlx_win || !instance->mlx_img.img)
		mlx_shutdown(instance);
	//raycast
	debug2D(instance);
	update_player(instance, instance->player.x, instance->player.y);
	//minimap
	vp_scaled(instance);
	vp_grid(instance);
	vp_player(instance, W_WIDTH / 9, W_HEIGHT - (MAP_SCALE * 2));
	//push to window
	mlx_put_image_to_window(instance->mlx_ser, instance->mlx_win, instance->mlx_img.img, 0, 0);
	mlx_hook(instance->mlx_win, KeyPress, KeyPressMask, handle_key, instance);
	mlx_hook(instance->mlx_win, KeyRelease, KeyReleaseMask, handle_key_release, instance);
	mlx_hook(instance->mlx_win, MotionNotify, PointerMotionMask, mouse_movement, instance);
	mlx_loop_hook(instance->mlx_ser, const_movement, instance);  // Use instance->mlx instead of instance->mlx_win
	mlx_hook(instance->mlx_win, DestroyNotify, StructureNotifyMask, exit_hook, instance);
	mlx_loop(instance->mlx_ser);
}
