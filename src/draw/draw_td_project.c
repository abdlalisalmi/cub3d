/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_td_project.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:59:50 by aes-salm          #+#    #+#             */
/*   Updated: 2020/11/26 12:26:42 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	get_texter_numbre(int i)
{
	if (!g_rays[i].was_hit_vertical && g_rays[i].ray_facing_up)
		g_norm.tx = 0;
	else if (!g_rays[i].was_hit_vertical && g_rays[i].ray_facing_down)
		g_norm.tx = 1;
	else if (g_rays[i].was_hit_vertical && g_rays[i].ray_facing_r)
		g_norm.tx = 2;
	else if (g_rays[i].was_hit_vertical && g_rays[i].ray_facing_l)
		g_norm.tx = 3;
}

int		wall_texture(int i, int y)
{
	g_norm.tx_offset_x = (g_rays[i].was_hit_vertical)
	? (int)g_rays[i].wall_hit_y % SQUARE : (int)g_rays[i].wall_hit_x % SQUARE;
	while (y < g_tr_project.wall_bottom_pixel)
	{
		get_texter_numbre(i);
		g_norm.tx_distance_ft = y
		+ (float)(g_tr_project.project_wall_height / 2)
		- (float)(g_file.window_h_td / 2);
		g_norm.tx_offset_y = g_norm.tx_distance_ft * ((float)SQUARE
		/ (float)g_tr_project.project_wall_height);
		g_norm.tx_offset_x = g_norm.tx_offset_x < 0 ? 0 : g_norm.tx_offset_x;
		g_norm.tx_offset_y = g_norm.tx_offset_y < 0 ? 0 : g_norm.tx_offset_y;
		g_texture[g_norm.tx].color = g_texture[g_norm.tx].colors[(SQUARE
		* g_norm.tx_offset_y) + g_norm.tx_offset_x];
		g_data.img_matrix_td[(g_file.window_w_td * y) + i] =
		g_texture[g_norm.tx].color;
		y++;
	}
	return (y);
}

void	fill_matrix_td(int i)
{
	int y;

	y = 0;
	while (y < g_tr_project.wall_top_pixel)
		g_data.img_matrix_td[(g_file.window_w_td *
		y++) + i] = g_file.sky_color;
	y = wall_texture(i, y);
	while (y < g_file.window_h_td)
		g_data.img_matrix_td[(g_file.window_w_td *
		y++) + i] = g_file.floor_color;
}

void	draw_td_project()
{
	int		i;

	i = 0;
	g_tr_project.distance_project_plane =
	(g_file.window_w_td / 2) / tanf(FOV_ANGLE / 2);
	while (i < g_file.window_w_td)
	{
		g_tr_project.real_distance = g_rays[i].wall_distance *
		cosf(g_rays[i].ray_angle - g_data.rotation);
		g_tr_project.project_wall_height = (float)(SQUARE /
		(g_tr_project.real_distance == 0 ? 0.1f : g_tr_project.real_distance)) *
		g_tr_project.distance_project_plane;
		g_tr_project.wall_top_pixel =
		(g_file.window_h_td / 2) - (g_tr_project.project_wall_height / 2);
		g_tr_project.wall_top_pixel =
		g_tr_project.wall_top_pixel < 0 ? 0 : g_tr_project.wall_top_pixel;
		g_tr_project.wall_bottom_pixel =
		(g_file.window_h_td / 2) + (g_tr_project.project_wall_height / 2);
		g_tr_project.wall_bottom_pixel =
		g_tr_project.wall_bottom_pixel > g_file.window_h_td ?
		g_file.window_h_td : g_tr_project.wall_bottom_pixel;
		fill_matrix_td(i);
		i++;
	}
}
