/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 20:12:25 by aes-salm          #+#    #+#             */
/*   Updated: 2020/10/17 14:26:37 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    cast_rays(t_struct *data, int colume_id)
{
    rays[colume_id].ray_facing_down = rays[colume_id].ray_angle > 0 && rays[colume_id].ray_angle < PI;
    rays[colume_id].ray_facing_up = !rays[colume_id].ray_facing_down;
    rays[colume_id].ray_facing_R = rays[colume_id].ray_angle < 0.5 * PI || rays[colume_id].ray_angle > 1.5 * PI;
    rays[colume_id].ray_facing_L = !rays[colume_id].ray_facing_R;



    float Xinter_cept;
    float Yinter_cept;
    float Xstep;
    float Ystep;

    rays[colume_id].was_hit_vertical = 0;
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
    Yinter_cept += rays[colume_id].ray_facing_down ? SQUARE : 0;
    
    Xinter_cept = data->px + (Yinter_cept - data->py) / tan(rays[colume_id].ray_angle);

    Ystep = SQUARE;
    Ystep *= rays[colume_id].ray_facing_up ? -1 : 1;

    Xstep = SQUARE / tan(rays[colume_id].ray_angle);
    Xstep *= (rays[colume_id].ray_facing_L && Xstep > 0) ? -1 : 1;
    Xstep *= (rays[colume_id].ray_facing_R && Xstep < 0) ? -1 : 1;

    next_horz_x = Xinter_cept;
    next_horz_y = Yinter_cept;

    while (next_horz_x >= 0 && next_horz_x <= (SQUARE * file.num_cols) && 
            next_horz_y >= 0 && next_horz_y <= (SQUARE * file.num_rows))
    {
        if (wall_check(next_horz_x, rays[colume_id].ray_facing_up ? next_horz_y - 1 : next_horz_y))
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
    float   next_vert_x;
    float   next_vert_y;
    int     found_vert_wall;
    float   wall_vert_hit_X;
    float   wall_vert_hit_Y;
    float   vert_hit_distance;

    found_vert_wall = 0;
    wall_vert_hit_X = 0;
    wall_vert_hit_Y = 0;

    Xinter_cept = floor(data->px / SQUARE) * SQUARE;
    Xinter_cept += rays[colume_id].ray_facing_R ? SQUARE : 0;
    
    Yinter_cept = data->py + (Xinter_cept - data->px) * tan(rays[colume_id].ray_angle);

    Xstep = SQUARE;
    Xstep *= rays[colume_id].ray_facing_L ? -1 : 1;

    Ystep = SQUARE * tan(rays[colume_id].ray_angle);
    Ystep *= (rays[colume_id].ray_facing_up && Ystep > 0) ? -1 : 1;
    Ystep *= (rays[colume_id].ray_facing_down && Ystep < 0) ? -1 : 1;

    next_vert_x = Xinter_cept;
    next_vert_y = Yinter_cept;

    while (next_vert_x >= 0 && next_vert_x <= (SQUARE * file.num_cols) && 
            next_vert_y >= 0 && next_vert_y <= (SQUARE * file.num_rows))
    {
        if (wall_check(rays[colume_id].ray_facing_L ? next_vert_x - 1: next_vert_x, next_vert_y))
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
    rays[colume_id].wall_hit_X = (horz_hit_distance < vert_hit_distance) ? wall_horz_hit_X : wall_vert_hit_X;
    rays[colume_id].wall_hit_Y = (horz_hit_distance < vert_hit_distance) ? wall_horz_hit_Y : wall_vert_hit_Y;
    rays[colume_id].wall_distance = (horz_hit_distance < vert_hit_distance) ? horz_hit_distance : vert_hit_distance;
    rays[colume_id].was_hit_vertical = (vert_hit_distance < horz_hit_distance);
}

void ray_draw(t_struct *data, int colume_id)
{
	float	x;
	float	y;
	int		i;

	i = 0;
	x = data->px;
	y = data->py;
	while (i <= rays[colume_id].wall_distance && x < (SQUARE * file.num_cols) && y < (SQUARE * file.num_rows))
	{
		data->img_matrix[((int)y * (SQUARE * file.num_cols)) + (int)x] = 0xf1c40f;
		x += cosf(rays[colume_id].ray_angle);
		y += sinf(rays[colume_id].ray_angle);
		i++;
	}
}

void draw_rays(t_struct *data)
{
	int		i;
	int		colume_id;
	float	ray_angle;

	colume_id = 0;
	ray_angle = data->rotation - (float)(FOV_ANGLE / 2);
	i = 0;
	while (i < file.window_w_td)
	{
		rays[colume_id].ray_angle = normalize_angle(ray_angle);
		cast_rays(data, colume_id);
		// ray_draw(data, colume_id);
		colume_id++;
		ray_angle += FOV_ANGLE / file.window_w_td;
		i++;
	}
}