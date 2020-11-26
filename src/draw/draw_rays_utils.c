/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 09:22:08 by aes-salm          #+#    #+#             */
/*   Updated: 2020/11/26 12:23:28 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	horizontal_wall_hint_calc(int colume_id)
{
	g_rnorm.yinter_cept = floor(g_data.py / SQUARE) * SQUARE;
	g_rnorm.yinter_cept += g_rays[colume_id].ray_facing_down ? SQUARE : 0;
	g_rnorm.xinter_cept = g_data.px + (g_rnorm.yinter_cept - g_data.py) /
	tan(g_rays[colume_id].ray_angle);
	g_rnorm.ystep = SQUARE;
	g_rnorm.ystep *= g_rays[colume_id].ray_facing_up ? -1 : 1;
	g_rnorm.xstep = SQUARE / tan(g_rays[colume_id].ray_angle);
	g_rnorm.xstep *= (g_rays[colume_id].ray_facing_l && g_rnorm.xstep > 0)
	? -1 : 1;
	g_rnorm.xstep *= (g_rays[colume_id].ray_facing_r && g_rnorm.xstep < 0)
	? -1 : 1;
	g_rnorm.next_horz_x = g_rnorm.xinter_cept;
	g_rnorm.next_horz_y = g_rnorm.yinter_cept;
}

void	horizontal_wall_hint_find(int colume_id)
{
	horizontal_wall_hint_calc(colume_id);
	while (g_rnorm.next_horz_x >= 0 && g_rnorm.next_horz_x <
	(SQUARE * g_file.num_cols) &&
			g_rnorm.next_horz_y >= 0 && g_rnorm.next_horz_y <
			(SQUARE * g_file.num_rows))
	{
		if (wall_check(g_rnorm.next_horz_x, g_rays[colume_id].ray_facing_up ?
		g_rnorm.next_horz_y - 1 : g_rnorm.next_horz_y))
		{
			g_rnorm.found_horz_wall = 1;
			g_rnorm.wall_horz_hit_x = g_rnorm.next_horz_x;
			g_rnorm.wall_horz_hit_y = g_rnorm.next_horz_y;
			break ;
		}
		else
		{
			g_rnorm.next_horz_x += g_rnorm.xstep;
			g_rnorm.next_horz_y += g_rnorm.ystep;
		}
	}
	g_rnorm.horz_hit_distance = (g_rnorm.found_horz_wall)
	? distance_between_points(g_data.px, g_data.py,
	g_rnorm.wall_horz_hit_x, g_rnorm.wall_horz_hit_y)
	: INT_MAX;
}

void	vertical_wall_hint_calc(int colume_id)
{
	g_rnorm.xinter_cept = floor(g_data.px / SQUARE) * SQUARE;
	g_rnorm.xinter_cept += g_rays[colume_id].ray_facing_r ? SQUARE : 0;
	g_rnorm.yinter_cept = g_data.py + (g_rnorm.xinter_cept - g_data.px) *
	tan(g_rays[colume_id].ray_angle);
	g_rnorm.xstep = SQUARE;
	g_rnorm.xstep *= g_rays[colume_id].ray_facing_l ? -1 : 1;
	g_rnorm.ystep = SQUARE * tan(g_rays[colume_id].ray_angle);
	g_rnorm.ystep *= (g_rays[colume_id].ray_facing_up && g_rnorm.ystep > 0)
	? -1 : 1;
	g_rnorm.ystep *= (g_rays[colume_id].ray_facing_down && g_rnorm.ystep < 0)
	? -1 : 1;
	g_rnorm.next_vert_x = g_rnorm.xinter_cept;
	g_rnorm.next_vert_y = g_rnorm.yinter_cept;
}

void	vertical_wall_hint_find(int colume_id)
{
	vertical_wall_hint_calc(colume_id);
	while (g_rnorm.next_vert_x >= 0 && g_rnorm.next_vert_x <
	(SQUARE * g_file.num_cols) &&
	g_rnorm.next_vert_y >= 0 && g_rnorm.next_vert_y <
	(SQUARE * g_file.num_rows))
	{
		if (wall_check(g_rays[colume_id].ray_facing_l ?
		g_rnorm.next_vert_x - 1 : g_rnorm.next_vert_x, g_rnorm.next_vert_y))
		{
			g_rnorm.found_vert_wall = 1;
			g_rnorm.wall_vert_hit_x = g_rnorm.next_vert_x;
			g_rnorm.wall_vert_hit_y = g_rnorm.next_vert_y;
			break ;
		}
		else
		{
			g_rnorm.next_vert_x += g_rnorm.xstep;
			g_rnorm.next_vert_y += g_rnorm.ystep;
		}
	}
	g_rnorm.vert_hit_distance = (g_rnorm.found_vert_wall)
	? distance_between_points(g_data.px, g_data.py,
	g_rnorm.wall_vert_hit_x, g_rnorm.wall_vert_hit_y)
	: INT_MAX;
}
