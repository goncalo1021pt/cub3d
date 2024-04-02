
#include "../includes/headers/cub3d.h"

int	main(int argc, char **argv)
{
	t_session *instance;

	(void)argv;
	if (argc == 2)
	{
		instance = (t_session *)malloc(sizeof(t_session));
		if (!instance)
			return (0);


		mlx_startup(instance);

	}
	return (0);
}
