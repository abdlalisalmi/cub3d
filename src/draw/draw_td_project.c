/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_td_project.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:59:50 by aes-salm          #+#    #+#             */
/*   Updated: 2020/11/25 11:46:20 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int		wall_texture(t_struct *data, int i, int y)
{
	norm.tx_offset_x = (rays[i].was_hit_vertical)
	? (int)rays[i].wall_hit_Y % SQUARE : (int)rays[i].wall_hit_X % SQUARE;
	while (y < tr_project.wall_bottom_pixel)
	{
		if (!rays[i].was_hit_vertical && rays[i].ray_facing_up)
			norm.tx = 0;
		else if (!rays[i].was_hit_vertical && rays[i].ray_facing_down)
			norm.tx = 1;
		else if (rays[i].was_hit_vertical && rays[i].ray_facing_R)
			norm.tx = 2;
		else if (rays[i].was_hit_vertical && rays[i].ray_facing_L)
			norm.tx = 3;
		norm.tx_distance_ft = y + (float)(tr_project.project_wall_height / 2)
		- (float)(file.window_h_td / 2);
		norm.tx_offset_y = norm.tx_distance_ft * ((float)SQUARE
		/ (float)tr_project.project_wall_height);
		norm.tx_offset_x = norm.tx_offset_x < 0 ? 0 : norm.tx_offset_x;
		norm.tx_offset_y = norm.tx_offset_y < 0 ? 0 : norm.tx_offset_y;
		texture[norm.tx].color = texture[norm.tx].colors[(SQUARE
		* norm.tx_offset_y) + norm.tx_offset_x];
		data->img_matrix_td[(file.window_w_td * y) + i] =
		texture[norm.tx].color;
		y++;
	}
	return (y);
}

void	fill_matrix_td(t_struct *data, int i)
{
	int y;

	y = 0;
	while (y < tr_project.wall_top_pixel)
		data->img_matrix_td[(file.window_w_td * y++) + i] = file.sky_color;
	y = wall_texture(data, i, y);
	while (y < file.window_h_td)
		data->img_matrix_td[(file.window_w_td * y++) + i] = file.floor_color;
}

void	draw_td_project(t_struct *data)
{
	int		i;

	i = 0;
	tr_project.distance_project_plane =
	(file.window_w_td / 2) / tanf(FOV_ANGLE / 2);
	while (i < file.window_w_td)
	{
		tr_project.real_distance = rays[i].wall_distance *
		cosf(rays[i].ray_angle - data->rotation);
		tr_project.project_wall_height = (float)(SQUARE /
		(tr_project.real_distance == 0 ? 0.1f : tr_project.real_distance)) *
		tr_project.distance_project_plane;
		tr_project.wall_top_pixel =
		(file.window_h_td / 2) - (tr_project.project_wall_height / 2);
		tr_project.wall_top_pixel =
		tr_project.wall_top_pixel < 0 ? 0 : tr_project.wall_top_pixel;
		tr_project.wall_bottom_pixel =
		(file.window_h_td / 2) + (tr_project.project_wall_height / 2);
		tr_project.wall_bottom_pixel =
		tr_project.wall_bottom_pixel > file.window_h_td ?
		file.window_h_td : tr_project.wall_bottom_pixel;
		fill_matrix_td(data, i);
		i++;
	}
}
