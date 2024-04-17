#include "../../includes/headers/cub3d.h"

bool	is_in_array(char *arr, char c)
{
	while (*arr)
	{
		if (c == *arr)
			return (true);
		arr++;
	}
	return (false);
}

bool	is_number(char *str)
{
	int	ctd;

	ctd = 0;
	while (str[ctd])
	{
		if (!ft_isdigit(str[ctd]))
			return (false);
		ctd++;
	}
	return (true);
}

int	ft_strslen(char **strs)
{
	int	ctd;

	ctd = 0;
	while (strs[ctd])
		ctd++;
	return (ctd);
}
