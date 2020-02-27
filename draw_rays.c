/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 20:12:25 by aes-salm          #+#    #+#             */
/*   Updated: 2020/02/26 20:55:58 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ray_draw(t_struct *data, int distance);

void    cast_rays(t_struct *data, int colume_id)
{

    data->ray_facing_down = data->ray_angle > 0 && data->ray_angle < PI;
    data->ray_facing_up = !data->ray_facing_down;
    data->ray_facing_R = data->ray_angle < 0.5 * PI || data->ray_angle > 1.5 * PI;
    data->ray_facing_L = !data->ray_facing_R;

    float wall_hit_x;
    float wall_hit_y;
    float distance;
    int was_hit_vertical;

    float Xinter_cept;
    float Yinter_cept;
    float Xstep;
    float Ystep;

    colume_id = 1;
    wall_hit_x = 0;
    wall_hit_y = 0;
    distance = 0;
    was_hit_vertical = 0;
/////////////////////////////////////////////////////////
//// horizontal wall hint find
////////////////////////////////////////////////////////
    float next_horz_x;
    float next_horz_y;
    int found_horz_wall;
    float wall_horz_hit_X;
    float wall_horz_hit_Y;
    float horz_hit_distance;

    found_horz_wall = 0;
    wall_horz_hit_X = 0;
    wall_horz_hit_Y = 0;

    Yinter_cept = floor(data->py / SQUARE) * SQUARE;
    Yinter_cept += data->ray_facing_down ? SQUARE : 0;
    
    Xinter_cept = data->px + (Yinter_cept - data->py) / tan(data->ray_angle);

    Ystep = SQUARE;
    Ystep *= data->ray_facing_up ? -1 : 1;

    Xstep = SQUARE / tan(data->ray_angle);
    Xstep *= (data->ray_facing_L && Xstep > 0) ? -1 : 1;
    Xstep *= (data->ray_facing_R && Xstep < 0) ? -1 : 1;

    next_horz_x = Xinter_cept;
    next_horz_y = Yinter_cept;

    if (data->ray_facing_up)
        next_horz_y--;
    while (next_horz_x >= 0 && next_horz_x <= WINDOW_WIDTH && 
            next_horz_y >= 0 && next_horz_y <= WINDOW_HIGHT)
    {
        if (wall_check(next_horz_x, next_horz_y))
        {
            found_horz_wall = 1;
            wall_horz_hit_X = next_horz_x;
            wall_horz_hit_Y = next_horz_y;
            break;
        }
        else
        {
            next_horz_x += Xstep;
            next_horz_y += Ystep;
        }
    }
    ////////////////////////// find distance horizontal //////////////
    horz_hit_distance = (found_horz_wall)
    ? distance_between_points(data->px, data->py, wall_horz_hit_X, wall_horz_hit_Y) 
    : INT_MAX;
/////////////////////////////////////////////////////////
//// vertical wall hint find
////////////////////////////////////////////////////////
    float next_vert_x;
    float next_vert_y;
    int found_vert_wall;
    float wall_vert_hit_X;
    float wall_vert_hit_Y;
    float vert_hit_distance;

    found_vert_wall = 0;
    wall_vert_hit_X = 0;
    wall_vert_hit_Y = 0;

    Xinter_cept = floor(data->px / SQUARE) * SQUARE;
    Xinter_cept += data->ray_facing_R ? SQUARE : 0;
    
    Yinter_cept = data->py + (Xinter_cept - data->px) * tan(data->ray_angle);

    Xstep = SQUARE;
    Xstep *= data->ray_facing_L ? -1 : 1;

    Ystep = SQUARE * tan(data->ray_angle);
    Ystep *= (data->ray_facing_up && Ystep > 0) ? -1 : 1;
    Ystep *= (data->ray_facing_down && Ystep < 0) ? -1 : 1;

    next_vert_x = Xinter_cept;
    next_vert_y = Yinter_cept;

    if (data->ray_facing_L)
        next_vert_x--;
    while (next_vert_x >= 0 && next_vert_x <= WINDOW_WIDTH && 
            next_vert_y >= 0 && next_vert_y <= WINDOW_HIGHT)
    {
        if (wall_check(next_vert_x, next_vert_y))
        {
            found_vert_wall = 1;
            wall_vert_hit_X = next_vert_x;
            wall_vert_hit_Y = next_vert_y;
            break;
        }
        else
        {
            next_vert_x += Xstep;
            next_vert_y += Ystep;
        }
    }
    ////////////////////////// find distance vertical //////////////

    vert_hit_distance = (found_vert_wall)
    ? distance_between_points(data->px, data->py, wall_vert_hit_X, wall_vert_hit_Y) 
    : INT_MAX;
    
    ///////////////////////////////////////////////////////////////////////////
    wall_hit_x = (horz_hit_distance < vert_hit_distance) ? wall_horz_hit_X : wall_vert_hit_X;
    wall_hit_y = (horz_hit_distance < vert_hit_distance) ? wall_horz_hit_Y : wall_vert_hit_Y;
    distance = (horz_hit_distance < vert_hit_distance) ? horz_hit_distance : vert_hit_distance;
    was_hit_vertical = (vert_hit_distance < horz_hit_distance);
    ray_draw(data, distance);
}

void ray_draw(t_struct *data, int distance)
{
    float x;
    float y;
    int i = 0;

    x = data->px;
    y = data->py;
    while (i < distance)
    {
        mlx_pixel_put(data->connection_id, data->window_id, x, y, 0xE84118);
        x += cosf(data->ray_angle);
        y += sinf(data->ray_angle);
        i++;
    }
}

void draw_rays(t_struct *data)
{
    int i;
    int colume_id;

    colume_id = 0;
    data->ray_angle = data->rotation - (float)(FOV_ANGLE / 2);
    i = 0;
    while (i < NUM_RAYS)
    {
        cast_rays(data, colume_id);
        data->ray_angle += FOV_ANGLE / NUM_RAYS;
        data->ray_angle = normalize_angle(data->ray_angle);
        i++;
        colume_id++;
    }
}