/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:44:54 by rlandolt          #+#    #+#             */
/*   Updated: 2024/04/26 12:44:55 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/cub3d.h"

bool	load_textures(t_session *ist)
{
	read_textures(ist);
	if (!ist->textures[NORTH_TEXTURE].img || !ist->textures[SOUTH_TEXTURE].img
		|| !ist->textures[WEST_TEXTURE].img || !ist->textures[EAST_TEXTURE].img
		|| !ist->textures[DOOR_TEXTURE_1].img)
		return (ft_putendl_fd(ERR_TEXTURE_LOAD, 2), false);
	get_tex_data_1(ist);
	return (true);
}
