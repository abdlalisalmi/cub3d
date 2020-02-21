/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:11:33 by aes-salm          #+#    #+#             */
/*   Updated: 2020/02/21 21:11:48 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     keypress(int keycode, t_struct *data)
{
    if (keycode == W)
        data->walk_direction = 1;
    else if (keycode == S)
        data->walk_direction= -1;
    else if (keycode == D)
        data->turn_direction = 1;
    else if (keycode == A)
        data->turn_direction = -1;
    return (0);
}

int     keyrelease(int keycode, t_struct *data)
{
    if (keycode == W)
        data->walk_direction= 0;
    else if (keycode == S)
        data->walk_direction = 0;
    else if (keycode == D)
        data->turn_direction = 0;
    else if (keycode == A)
        data->turn_direction = 0;
    return (0);
}