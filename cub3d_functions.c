/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 21:08:56 by aes-salm          #+#    #+#             */
/*   Updated: 2020/02/26 20:44:54 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float     distance_between_points(float x1, float y1, float x2, float y2)
{
    return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

float   normalize_angle(float angle)
{
    if (angle >= (2 * PI))
        angle -= (2 * PI);
    else if (angle <= 0)
        angle += (2 * PI);
    return (angle);
}
