#include "../../includes/headers/cub3d.h"

int	handle_mode(int keycode, t_session *instance)
{
	if (keycode == XK_p)
	{
		if (instance->mode.type == PAUSE)
		{
			instance->mode.type = PLAY;
			mlx_mouse_hide(instance->mlx_ser, instance->mlx_win);
		}
		else
		{
			instance->mode.type = PAUSE;
			mlx_mouse_show(instance->mlx_ser, instance->mlx_win);
			pause_menu(instance);
		}
	}
	else if (keycode == XK_Tab && instance->mode.type == PLAY && instance->mode.sub == DEFAULT)
		instance->mode.sub = MINIMAP;
	else if (keycode == XK_Tab && instance->mode.type == PLAY && instance->mode.sub == MINIMAP)
		instance->mode.sub = DEFAULT;
	return (0);
}

void	handle_door(t_session *instance)
{
	struct timeval		tv;

	if (instance->player.door)
		return ;
	gettimeofday(&tv, NULL);
	instance->player.time_door = tv.tv_sec;
	instance->player.door = true;
}

void	choose_door_texture(t_session *instance, struct timeval tv)
{
	if (instance->player.door == false)
		return ;
	if (tv.tv_sec < instance->player.time_door + 1)
	{
		if ((float)instance->player.time_door - tv.tv_usec / 1000000 < 1 / 4)
			instance->textures[DOOR_TEXTURE] = instance->textures[DOOR_TEXTURE_2];
		else if ((float)instance->player.time_door - tv.tv_usec / 1000000 < 2 / 4)
			instance->textures[DOOR_TEXTURE] = instance->textures[DOOR_TEXTURE_3];
		else if ((float)instance->player.time_door - tv.tv_usec / 1000000 < 3 / 4)
			instance->textures[DOOR_TEXTURE] = instance->textures[DOOR_TEXTURE_4];
		else
			instance->textures[DOOR_TEXTURE] = instance->textures[DOOR_TEXTURE_5];
	}
	else if (tv.tv_sec > instance->player.time_door + 4)
	{
		if ((float)instance->player.time_door + 4 - tv.tv_usec / 1000000 < 1 / 4)
			instance->textures[DOOR_TEXTURE] = instance->textures[DOOR_TEXTURE_4];
		else if ((float)instance->player.time_door - tv.tv_usec / 1000000 < 2 / 4)
			instance->textures[DOOR_TEXTURE] = instance->textures[DOOR_TEXTURE_3];
		else if ((float)instance->player.time_door - tv.tv_usec / 1000000 < 3 / 4)
			instance->textures[DOOR_TEXTURE] = instance->textures[DOOR_TEXTURE_2];
		else
			instance->textures[DOOR_TEXTURE] = instance->textures[DOOR_TEXTURE_1];
	}
}

void	close_door(t_session *instance)
{
	struct timeval		tv;

	if (instance->player.door == false)
		return ;
	gettimeofday(&tv, NULL);
	if (tv.tv_sec < instance->player.time_door + 1 || tv.tv_sec > instance->player.time_door + 4)
		choose_door_texture(instance, tv);
	if (instance->player.time_door + 5 > tv.tv_sec)
		return ;
	instance->player.door = false;
}
