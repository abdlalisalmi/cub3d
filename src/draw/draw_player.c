/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 22:57:35 by aes-salm          #+#    #+#             */
/*   Updated: 2020/11/26 12:27:04 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	move_player()
{
	float	move_step;
	float	next_px;
	float	next_py;

	g_data.rotation += g_data.turn_direction * g_data.rotation_speed;
	g_data.rotation = normalize_angle(g_data.rotation);
	move_step = g_data.walk_direction * g_data.move_speed;
	next_px = g_data.px + cosf(g_data.rotation + g_data.side) * move_step;
	next_py = g_data.py + sinf(g_data.rotation + g_data.side) * move_step;
	if (!wall_check(next_px, g_data.py) && !sprite_check(next_px, g_data.py))
		g_data.px = next_px;
	if (!wall_check(g_data.px, next_py) && !sprite_check(g_data.px, next_py))
		g_data.py = next_py;
}

void	draw_player()
{
	move_player();
}
