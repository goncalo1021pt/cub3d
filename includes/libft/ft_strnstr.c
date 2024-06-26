/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goncalo1021pt <goncalo1021pt@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:02:28 by gfontao-          #+#    #+#             */
/*   Updated: 2024/04/23 23:47:49 by goncalo1021      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *str, const char *to_find, size_t len)
{
	size_t	ctd;
	size_t	ctd2;

	ctd = 0;
	ctd2 = 0;
	if (*to_find == '\0')
		return (str);
	while (str[ctd] && ctd < len)
	{
		if (str[ctd] == to_find[ctd2])
		{
			while (to_find[ctd2] && (ctd + ctd2) < len)
			{
				if (to_find[ctd2] != str[ctd + ctd2])
					break ;
				ctd2++;
			}
			if (ctd2 == ft_strlen(to_find))
				return (str + ctd);
			ctd2 = 0;
		}
		ctd++;
	}
	return (0);
}
