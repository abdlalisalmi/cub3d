/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 20:12:25 by aes-salm          #+#    #+#             */
/*   Updated: 2020/11/26 12:25:31 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	init_rays_variables(void)
{
	g_rnorm.found_horz_wall = 0;
	g_rnorm.wall_horz_hit_x = 0;
	g_rnorm.wall_horz_hit_y = 0;
	g_rnorm.found_vert_wall = 0;
	g_rnorm.wall_vert_hit_x = 0;
	g_rnorm.wall_vert_hit_y = 0;
}

void	cast_rays(int colume_id)
{
	g_rays[colume_id].ray_facing_down = g_rays[colume_id].ray_angle > 0 &&
	g_rays[colume_id].ray_angle < PI;
	g_rays[colume_id].ray_facing_up = !g_rays[colume_id].ray_facing_down;
	g_rays[colume_id].ray_facing_r = g_rays[colume_id].ray_angle < 0.5 * PI ||
	g_rays[colume_id].ray_angle > 1.5 * PI;
	g_rays[colume_id].ray_facing_l = !g_rays[colume_id].ray_facing_r;
	g_rays[colume_id].was_hit_vertical = 0;
	horizontal_wall_hint_find(colume_id);
	vertical_wall_hint_find(colume_id);
	g_rays[colume_id].wall_hit_x =
	(g_rnorm.horz_hit_distance < g_rnorm.vert_hit_distance) ?
	g_rnorm.wall_horz_hit_x : g_rnorm.wall_vert_hit_x;
	g_rays[colume_id].wall_hit_y =
	(g_rnorm.horz_hit_distance < g_rnorm.vert_hit_distance) ?
	g_rnorm.wall_horz_hit_y : g_rnorm.wall_vert_hit_y;
	g_rays[colume_id].wall_distance =
	(g_rnorm.horz_hit_distance < g_rnorm.vert_hit_distance) ?
	g_rnorm.horz_hit_distance : g_rnorm.vert_hit_distance;
	g_rays[colume_id].was_hit_vertical =
	(g_rnorm.vert_hit_distance < g_rnorm.horz_hit_distance);
}

void	draw_rays()
{
	int		i;
	int		colume_id;
	float	ray_angle;

    g_rays = (t_rays *)malloc(sizeof(t_rays) * g_file.window_w_td);
	colume_id = 0;
	ray_angle = g_data.rotation - (float)(FOV_ANGLE / 2);
	i = 0;
	while (i < g_file.window_w_td)
	{
		init_rays_variables();
		g_rays[colume_id].ray_angle = normalize_angle(ray_angle);
		cast_rays(colume_id);
		colume_id++;
		ray_angle += FOV_ANGLE / g_file.window_w_td;
		i++;
	}
    free(g_rays);
}
