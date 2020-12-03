/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 16:32:14 by aes-salm          #+#    #+#             */
/*   Updated: 2020/11/27 11:04:15 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int		update(void)
{
	draw_rays();
	draw_td_project();
	draw_player();
	draw_sprites();
	if (g_file.save_flag)
		create_bmp_file();
	mlx_put_image_to_window(g_data.connection_id, g_data.window_id,
	g_data.image_td, 0, 0);
	return (0);
}
