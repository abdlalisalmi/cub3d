/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:11:33 by aes-salm          #+#    #+#             */
/*   Updated: 2020/10/22 10:47:54 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     keypress(int keycode, t_struct *data)
{
    if (keycode == W)
        data->walk_direction = 1;
    else if (keycode == S)
        data->walk_direction= -1;
    else if (keycode == RIGHT)
        data->turn_direction = 1;
    else if (keycode == LEFT)
        data->turn_direction = -1;
    else if (keycode == A)
    {
        data->side = -(PI / 2);
        data->walk_direction = 1;
    }
    else if (keycode == D)
    {
        data->side = PI / 2;
        data->walk_direction = 1;
    }
    return (0);
}

int     keyrelease(int keycode, t_struct *data)
{
    if (keycode == W)
        data->walk_direction= 0;
    else if (keycode == S)
        data->walk_direction = 0;
    else if (keycode == RIGHT)
        data->turn_direction = 0;
    else if (keycode == LEFT)
        data->turn_direction = 0;
    else if (keycode == A || keycode == D)
    {
        data->side = 0;
        data->walk_direction = 0;
    }
    return (0);
}