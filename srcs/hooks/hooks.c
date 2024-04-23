#include "../../includes/headers/cub3d.h"

int	exit_hook(t_session *instance)
{
	mlx_shutdown(instance);
	return (0);
}

int	handle_key(int keycode, t_session *instance)
{
	//printf("\033[1;33mINPUT -> %d <- /////\033[0m\n", keycode);
	if (keycode == XK_Left)
		instance->keys[LEFT_ARROW] = 1;
	if (keycode == XK_Right)
		instance->keys[RIGHT_ARROW] = 1;
	if (keycode == XK_Shift_L)
		instance->keys[L_SHIFT] = 1;
	if (keycode == ESC)
		mlx_shutdown(instance);
	if (keycode == 'a')
		instance->keys[A] = 1;
	else if (keycode == 'd')
		instance->keys[D] = 1;
	else if (keycode == 'w')
		instance->keys[W] = 1;
	else if (keycode == 's')
		instance->keys[S] = 1;
	else
		return (0);
	instance->player.keys_pressed++;
	return (0);
}

int	handle_key_release(int keycode, t_session *instance)
{
	if (keycode == XK_Left)
		instance->keys[LEFT_ARROW] = 0;
	if (keycode == XK_Right)
		instance->keys[RIGHT_ARROW] = 0;
	if (keycode == XK_Shift_L)
		instance->keys[L_SHIFT] = 0;
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

void	check_time(void)
{
	struct timeval		tv;
	long long			current_time;
	static long long	last_time = 0;

	gettimeofday(&tv, NULL);
	current_time = (tv.tv_sec * (long)1000) + (tv.tv_usec / 1000);
	if (last_time && current_time - last_time <= FRAME_TIME)
		usleep(FRAME_TIME - (current_time - last_time <= FRAME_TIME));
	gettimeofday(&tv, NULL);
	last_time = (tv.tv_sec * (long)1000) + (tv.tv_usec / 1000);
}

int	const_movement(t_session *instance)
{
	int	speed;

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
	check_time();
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
