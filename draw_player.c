/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 22:57:35 by aes-salm          #+#    #+#             */
/*   Updated: 2020/02/21 23:23:28 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int wall_check(t_struct *data)
// {
//     return (0);
// }

void    draw(t_struct *data)
{
    int i = data->px - 3;
    int j = data->py - 3;
    while (i <= data->px + 6)
    {
        while (j <= data->py + 6)
        {
            mlx_pixel_put(data->connection_id, data->window_id, i, j, 0xE84118);
            j++;
        }
        j = data->py - 3;
        i++;
    }
}

void move_player(t_struct *data)
{
    float MoveStep;
    MoveStep = data->walk_direction * data->move_speed;
    data->px += cosf(data->rotation) * MoveStep;
    data->py += sinf(data->rotation) * MoveStep;
}

void rotate_player(t_struct *data)
{
    float x;
    float y;
    int i = 0;

    x = data->px;
    y = data->py;
    data->rotation += data->turn_direction * data->turn_speed;
    while (i < 30)
    {
        mlx_pixel_put(data->connection_id, data->window_id, x, y, 0xE84118);
        x += cosf(data->rotation);
        y += sinf(data->rotation);
        i++;
    }
}

void draw_player(t_struct *data)
{
    draw(data);
    rotate_player(data);
    move_player(data);
}