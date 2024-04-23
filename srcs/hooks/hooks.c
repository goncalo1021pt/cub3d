#include "../../includes/headers/cub3d.h"

int	exit_hook(t_session *instance)
{
	mlx_shutdown(instance);
	return (0);
}

int	handle_key(int keycode, t_session *instance)
{
	if (keycode == XK_Left)
		instance->keys[LEFT_ARROW] = 1;
	else if (keycode == XK_Right)
		instance->keys[RIGHT_ARROW] = 1;
	else if (keycode == XK_Shift_L)
		instance->keys[L_SHIFT] = 1;
	else if (keycode == XK_Escape)
		mlx_shutdown(instance);
	if (keycode == XK_a)
		instance->keys[A] = 1;
	else if (keycode == XK_d)
		instance->keys[D] = 1;
	else if (keycode == XK_w)
		instance->keys[W] = 1;
	else if (keycode == XK_s)
		instance->keys[S] = 1;
	else 
		return (0);
	instance->player.keys_pressed++;
	return (0);
}

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

int	handle_key_release(int keycode, t_session *instance)
{
	if (keycode == XK_Left)
		instance->keys[LEFT_ARROW] = 0;
	else if (keycode == XK_Right)
		instance->keys[RIGHT_ARROW] = 0;
	else if (keycode == XK_Shift_L)
		instance->keys[L_SHIFT] = 0;
	else if (keycode == XK_p)
		handle_mode(keycode, instance);
	else if (keycode == XK_Tab)
		handle_mode(keycode, instance);
	if (keycode == 'a')
		instance->keys[A] = 0;
	else if (keycode == 'd')
		instance->keys[D] = 0;
	else if (keycode == 'w')
		instance->keys[W] = 0;
	else if (keycode == 's')
		instance->keys[S] = 0;
	else
		return (0);
	instance->player.keys_pressed--;
	return (0);
}

// int handle_static_keys(int keycode, t_session *instance)
// {
// 	if (keycode == XK_Tab)
// 		instance.
// }

int	const_movement(t_session *instance)
{
	int	speed;

	if (instance->mode.type == PAUSE)
		return (0);
	speed = get_player_speed(instance);
	if (instance->keys[W])
		move_player(&instance->player, &instance->map, speed, W_ANGLE);
	if (instance->keys[S])
		move_player(&instance->player, &instance->map, speed, S_ANGLE);
	if (instance->keys[A])
		move_player(&instance->player, &instance->map, speed, A_ANGLE);
	if (instance->keys[D])
		move_player(&instance->player, &instance->map, speed, D_ANGLE);
	if (instance->keys[LEFT_ARROW])
		rotate_player(&instance->player, LEFT_ARROW);
	if (instance->keys[RIGHT_ARROW])
		rotate_player(&instance->player, RIGHT_ARROW);
	mlx_update(instance);
	return (0);
}

// int	handle_key(int keycode, t_session *instance)
// {
// 	if (keycode == 65307)
// 		mlx_shutdown(instance);
// 	if (keycode == 'a')
// 	{
// 		move_player(&instance->player, &instance->map, 1, A_ANGLE);
// 	}
// 	if (keycode == 'd')
// 		instance->keycode = 'd';
// 	if (keycode == 'w')
// 	{
// 		ft_printf("w");
// 		move_player(&instance->player, &instance->map, 1, W_ANGLE);
// 	}
// 	if (keycode == 's')
// 		instance->keycode = 's';
// 	return (0);
// }
