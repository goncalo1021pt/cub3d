#include "../../includes/headers/cub3d.h"

void	choose_open_textures(t_session *instance, float elapsed_time)
{
	if (elapsed_time < 1 / 4.0)
		instance->textures[DOOR_TEXTURE] = instance->textures[DOOR_TEXTURE_2];
	else if (elapsed_time < 2 / 4.0)
		instance->textures[DOOR_TEXTURE] = instance->textures[DOOR_TEXTURE_3];
	else if (elapsed_time < 3 / 4.0)
		instance->textures[DOOR_TEXTURE] = instance->textures[DOOR_TEXTURE_4];
	else
		instance->textures[DOOR_TEXTURE] = instance->textures[DOOR_TEXTURE_5];
}

void	choose_close_textures(t_session *instance, float elapsed_time)
{
	if (elapsed_time - 4 < 1 / 4.0)
		instance->textures[DOOR_TEXTURE] = instance->textures[DOOR_TEXTURE_4];
	else if (elapsed_time - 4 < 2 / 4.0)
		instance->textures[DOOR_TEXTURE] = instance->textures[DOOR_TEXTURE_3];
	else if (elapsed_time - 4 < 3 / 4.0)
		instance->textures[DOOR_TEXTURE] = instance->textures[DOOR_TEXTURE_2];
	else
		instance->textures[DOOR_TEXTURE] = instance->textures[DOOR_TEXTURE_1];
}

void	choose_door_texture(t_session *instance, struct timeval tv)
{
	float	elapsed_time;

	if (instance->player.door == false)
		return ;
	elapsed_time = tv.tv_sec - instance->player.time_door + tv.tv_usec
		/ 1000000.0;
	if (elapsed_time < 1)
		choose_open_textures(instance, elapsed_time);
	else if (elapsed_time > 4)
		choose_close_textures(instance, elapsed_time);
}
