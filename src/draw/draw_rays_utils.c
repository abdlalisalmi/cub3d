/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 09:22:08 by aes-salm          #+#    #+#             */
/*   Updated: 2020/11/25 10:17:04 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	horizontal_wall_hint_calc(int colume_id)
{
	rnorm.Yinter_cept = floor(data->py / SQUARE) * SQUARE;
	rnorm.Yinter_cept += rays[colume_id].ray_facing_down ? SQUARE : 0;
	rnorm.Xinter_cept = data->px + (rnorm.Yinter_cept - data->py) /
	tan(rays[colume_id].ray_angle);
	rnorm.Ystep = SQUARE;
	rnorm.Ystep *= rays[colume_id].ray_facing_up ? -1 : 1;
	rnorm.Xstep = SQUARE / tan(rays[colume_id].ray_angle);
	rnorm.Xstep *= (rays[colume_id].ray_facing_L && rnorm.Xstep > 0) ? -1 : 1;
	rnorm.Xstep *= (rays[colume_id].ray_facing_R && rnorm.Xstep < 0) ? -1 : 1;
	rnorm.next_horz_x = rnorm.Xinter_cept;
	rnorm.next_horz_y = rnorm.Yinter_cept;
}

void	horizontal_wall_hint_find(int colume_id)
{
	horizontal_wall_hint_calc(colume_id);
	while (rnorm.next_horz_x >= 0 && rnorm.next_horz_x <
	(SQUARE * file.num_cols) &&
			rnorm.next_horz_y >= 0 && rnorm.next_horz_y <
			(SQUARE * file.num_rows))
	{
		if (wall_check(rnorm.next_horz_x, rays[colume_id].ray_facing_up ?
		rnorm.next_horz_y - 1 : rnorm.next_horz_y))
		{
			rnorm.found_horz_wall = 1;
			rnorm.wall_horz_hit_X = rnorm.next_horz_x;
			rnorm.wall_horz_hit_Y = rnorm.next_horz_y;
			break ;
		}
		else
		{
			rnorm.next_horz_x += rnorm.Xstep;
			rnorm.next_horz_y += rnorm.Ystep;
		}
	}
	rnorm.horz_hit_distance = (rnorm.found_horz_wall)
	? distance_between_points(data->px, data->py,
	rnorm.wall_horz_hit_X, rnorm.wall_horz_hit_Y)
	: INT_MAX;
}

void	vertical_wall_hint_calc(int colume_id)
{
	rnorm.Xinter_cept = floor(data->px / SQUARE) * SQUARE;
	rnorm.Xinter_cept += rays[colume_id].ray_facing_R ? SQUARE : 0;
	rnorm.Yinter_cept = data->py + (rnorm.Xinter_cept - data->px) *
	tan(rays[colume_id].ray_angle);
	rnorm.Xstep = SQUARE;
	rnorm.Xstep *= rays[colume_id].ray_facing_L ? -1 : 1;
	rnorm.Ystep = SQUARE * tan(rays[colume_id].ray_angle);
	rnorm.Ystep *= (rays[colume_id].ray_facing_up && rnorm.Ystep > 0) ? -1 : 1;
	rnorm.Ystep *= (rays[colume_id].ray_facing_down && rnorm.Ystep < 0)
	? -1 : 1;
	rnorm.next_vert_x = rnorm.Xinter_cept;
	rnorm.next_vert_y = rnorm.Yinter_cept;
}

void	vertical_wall_hint_find(int colume_id)
{
	vertical_wall_hint_calc(colume_id);
	while (rnorm.next_vert_x >= 0 && rnorm.next_vert_x <
	(SQUARE * file.num_cols) &&
	rnorm.next_vert_y >= 0 && rnorm.next_vert_y <
	(SQUARE * file.num_rows))
	{
		if (wall_check(rays[colume_id].ray_facing_L ?
		rnorm.next_vert_x - 1 : rnorm.next_vert_x, rnorm.next_vert_y))
		{
			rnorm.found_vert_wall = 1;
			rnorm.wall_vert_hit_X = rnorm.next_vert_x;
			rnorm.wall_vert_hit_Y = rnorm.next_vert_y;
			break ;
		}
		else
		{
			rnorm.next_vert_x += rnorm.Xstep;
			rnorm.next_vert_y += rnorm.Ystep;
		}
	}
	rnorm.vert_hit_distance = (rnorm.found_vert_wall)
	? distance_between_points(data->px, data->py,
	rnorm.wall_vert_hit_X, rnorm.wall_vert_hit_Y)
	: INT_MAX;
}
