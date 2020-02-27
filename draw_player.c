/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 22:57:35 by aes-salm          #+#    #+#             */
/*   Updated: 2020/02/26 20:43:34 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void move_player(t_struct *data)
{
    float MoveStep;
    float nextPX;
    float nextPY;

    data->rotation += data->turn_direction * data->rotation_speed;
    data->rotation = normalize_angle(data->rotation);
    MoveStep = data->walk_direction * data->move_speed;
    nextPX = data->px + cosf(data->rotation) * MoveStep;
    nextPY = data->py + sinf(data->rotation) * MoveStep;
    if (!(wall_check(nextPX, nextPY)))
    {
        data->px = nextPX;
        data->py = nextPY;
    }
}

void draw_player(t_struct *data)
{
    mlx_pixel_put(data->connection_id, data->window_id, data->px, data->py, 0xE84118);
    move_player(data);
}