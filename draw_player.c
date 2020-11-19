/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 22:57:35 by aes-salm          #+#    #+#             */
/*   Updated: 2020/10/26 10:37:32 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_struct *data)
{
	float	MoveStep;
	float	nextPX;
	float	nextPY;

	data->rotation += data->turn_direction * data->rotation_speed;
	data->rotation = normalize_angle(data->rotation);
	MoveStep = data->walk_direction * data->move_speed;
	nextPX = data->px + cosf(data->rotation + data->side) * MoveStep;
	nextPY = data->py + sinf(data->rotation + data->side) * MoveStep;
	if (!wall_check(nextPX, data->py) && !sprite_check(nextPX, data->py))
		data->px = nextPX;
	if (!wall_check(data->px, nextPY) && !sprite_check(data->px, nextPY))
		data->py = nextPY;
}

void	draw_player(t_struct *data)
{
	move_player(data);
	// mlx_pixel_put(data->connection_id, data->window_id, data->px, data->py, 0xf1c40f);
}
