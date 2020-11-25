/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 20:12:25 by aes-salm          #+#    #+#             */
/*   Updated: 2020/11/25 09:57:37 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	init_rays_variables(void)
{
	rnorm.found_horz_wall = 0;
	rnorm.wall_horz_hit_X = 0;
	rnorm.wall_horz_hit_Y = 0;
	rnorm.found_vert_wall = 0;
	rnorm.wall_vert_hit_X = 0;
	rnorm.wall_vert_hit_Y = 0;
}

void	cast_rays(int colume_id)
{
	rays[colume_id].ray_facing_down = rays[colume_id].ray_angle > 0 &&
	rays[colume_id].ray_angle < PI;
	rays[colume_id].ray_facing_up = !rays[colume_id].ray_facing_down;
	rays[colume_id].ray_facing_R = rays[colume_id].ray_angle < 0.5 * PI ||
	rays[colume_id].ray_angle > 1.5 * PI;
	rays[colume_id].ray_facing_L = !rays[colume_id].ray_facing_R;
	rays[colume_id].was_hit_vertical = 0;
	horizontal_wall_hint_find(colume_id);
	vertical_wall_hint_find(colume_id);
	rays[colume_id].wall_hit_X =
	(rnorm.horz_hit_distance < rnorm.vert_hit_distance) ?
	rnorm.wall_horz_hit_X : rnorm.wall_vert_hit_X;
	rays[colume_id].wall_hit_Y =
	(rnorm.horz_hit_distance < rnorm.vert_hit_distance) ?
	rnorm.wall_horz_hit_Y : rnorm.wall_vert_hit_Y;
	rays[colume_id].wall_distance =
	(rnorm.horz_hit_distance < rnorm.vert_hit_distance) ?
	rnorm.horz_hit_distance : rnorm.vert_hit_distance;
	rays[colume_id].was_hit_vertical =
	(rnorm.vert_hit_distance < rnorm.horz_hit_distance);
}

void	draw_rays(t_struct *data)
{
	int		i;
	int		colume_id;
	float	ray_angle;

	colume_id = 0;
	ray_angle = data->rotation - (float)(FOV_ANGLE / 2);
	i = 0;
	while (i < file.window_w_td)
	{
		init_rays_variables();
		rays[colume_id].ray_angle = normalize_angle(ray_angle);
		cast_rays(colume_id);
		colume_id++;
		ray_angle += FOV_ANGLE / file.window_w_td;
		i++;
	}
}
