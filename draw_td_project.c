/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_td_project.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:59:50 by aes-salm          #+#    #+#             */
/*   Updated: 2020/03/12 22:27:06 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		wall_texture(t_struct *data, int i, int y)
{
	int offsetX;
	int offsetY;
	float distanceFT;
	int tx = 0;

	offsetX = (rays[i].was_hit_vertical) ? (int)rays[i].wall_hit_Y % SQUARE
					: (int)rays[i].wall_hit_X % SQUARE;

	while (y < tr_project.wall_bottom_pixel)
	{
		if (!rays[i].was_hit_vertical && rays[i].ray_facing_up)
			tx = 0;
		else if (!rays[i].was_hit_vertical && rays[i].ray_facing_down)
			tx = 1;
		else if (rays[i].was_hit_vertical && rays[i].ray_facing_R)
			tx = 2;
		else if (rays[i].was_hit_vertical && rays[i].ray_facing_L)
			tx = 3;
		//tx = (rays[i].was_hit_vertical && rays[i].ray_facing_down) ? 1 : tx;
		//tx = (rays[i].was_hit_vertical && rays[i].ray_facing_R) ? 2 : tx;
		//tx = (rays[i].was_hit_vertical && rays[i].ray_facing_R) ? 3 : tx;

		distanceFT = y + (float)(tr_project.project_wall_height / 2) - (float)(WINDOW_H_TD / 2);
		offsetY = distanceFT * ((float)SQUARE / (float)tr_project.project_wall_height);
		texture[tx].color = texture[tx].colors[(SQUARE * offsetY) + offsetX];
		data->img_matrix_td[(WINDOW_W_TD * y) + i] = texture[tx].color;
		y++;
	}
	return (y);
}

void	fill_matrix_td(t_struct *data, int i)
{
	int y;

	y = 0;
	while (y < tr_project.wall_top_pixel)
		data->img_matrix_td[(WINDOW_W_TD * y++) + i] = 0x45aaf2;

	y = wall_texture(data, i, y);

	while (y < WINDOW_H_TD)
		data->img_matrix_td[(WINDOW_W_TD * y++) + i] = 0x218c74;
}

void	draw_td_project(t_struct *data)
{
	int		i;

	i = 0;
	tr_project.distance_project_plane =
	(WINDOW_W_TD / 2) / tanf(FOV_ANGLE / 2);
	while (i < NUM_RAYS)
	{
		tr_project.real_distance = rays[i].wall_distance *
		cosf(rays[i].ray_angle - data->rotation);
		tr_project.project_wall_height = (float)(SQUARE /
		(tr_project.real_distance == 0 ? 0.1f : tr_project.real_distance)) *
		tr_project.distance_project_plane;
		tr_project.wall_top_pixel =
		(WINDOW_H_TD / 2) - (tr_project.project_wall_height / 2);
		tr_project.wall_top_pixel =
		tr_project.wall_top_pixel < 0 ? 0 : tr_project.wall_top_pixel;
		tr_project.wall_bottom_pixel =
		(WINDOW_H_TD / 2) + (tr_project.project_wall_height / 2);
		tr_project.wall_bottom_pixel =
		tr_project.wall_bottom_pixel > WINDOW_H_TD ?
		WINDOW_H_TD : tr_project.wall_bottom_pixel;
		fill_matrix_td(data,i);
		i++;
	}
}
