/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_td_project.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:59:50 by aes-salm          #+#    #+#             */
/*   Updated: 2020/03/10 20:14:16 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_matrix_td(t_struct *data, int i)
{
	int y;

	y = 0;
	while (y < tr_project.wall_top_pixel)
		data->img_matrix_td[(WINDOW_WIDTH * y++) + i] = 0x45aaf2;
	while (y < tr_project.wall_bottom_pixel)
		data->img_matrix_td[(WINDOW_WIDTH * y++) + i] = 0x2c3e50;

	while (y < WINDOW_HIGHT)
		data->img_matrix_td[(WINDOW_WIDTH * y++) + i] = 0x218c74;
}

void	draw_td_project(t_struct *data)
{
	int		i;

	i = 0;
	tr_project.distance_project_plane =
	(WINDOW_WIDTH / 2) / tanf(FOV_ANGLE / 2);
	while (i < NUM_RAYS)
	{
		tr_project.real_distance = rays[i].wall_distance *
		cosf(rays[i].ray_angle - data->rotation);
		tr_project.project_wall_height = (float)(SQUARE /
		(tr_project.real_distance == 0 ? 0.1f : tr_project.real_distance)) *
		tr_project.distance_project_plane;
		tr_project.wall_top_pixel =
		(WINDOW_HIGHT / 2) - (tr_project.project_wall_height / 2);
		tr_project.wall_top_pixel =
		tr_project.wall_top_pixel < 0 ? 0 : tr_project.wall_top_pixel;
		tr_project.wall_bottom_pixel =
		(WINDOW_HIGHT / 2) + (tr_project.project_wall_height / 2);
		tr_project.wall_bottom_pixel =
		tr_project.wall_bottom_pixel > WINDOW_HIGHT ?
		WINDOW_HIGHT : tr_project.wall_bottom_pixel;
		fill_matrix_td(data,i);
		i++;
	}
}
