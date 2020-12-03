/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_components_check.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 13:51:38 by aes-salm          #+#    #+#             */
/*   Updated: 2020/12/03 11:14:02 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	file_components_check(void)
{
	if (!g_file.window_w_td || !g_file.window_h_td)
		print_errors("You haven't added the resolution values!!");
	if (!g_file.floor_color)
		print_errors("You haven't added the floor color value!!");
	if (!g_file.sky_color)
		print_errors("You haven't added the sky color value!!");
	if (!g_file.no_texture[0] || !g_file.so_texture[0] ||
	!g_file.we_texture[0] || !g_file.ea_texture[0])
		print_errors("You haven't added the walls textures values!!");
	if (!g_file.sprite_texture[0])
		print_errors("You haven't added the sprite texture value!!");
}
