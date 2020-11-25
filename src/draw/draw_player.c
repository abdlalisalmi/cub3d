/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 22:57:35 by aes-salm          #+#    #+#             */
/*   Updated: 2020/11/25 11:15:03 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	move_player(t_struct *data)
{
	float	move_step;
	float	next_px;
	float	next_py;

	data->rotation += data->turn_direction * data->rotation_speed;
	data->rotation = normalize_angle(data->rotation);
	move_step = data->walk_direction * data->move_speed;
	next_px = data->px + cosf(data->rotation + data->side) * move_step;
	next_py = data->py + sinf(data->rotation + data->side) * move_step;
	if (!wall_check(next_px, data->py) && !sprite_check(next_px, data->py))
		data->px = next_px;
	if (!wall_check(data->px, next_py) && !sprite_check(data->px, next_py))
		data->py = next_py;
}

void	draw_player(t_struct *data)
{
	move_player(data);
}
