/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 11:55:04 by aes-salm          #+#    #+#             */
/*   Updated: 2020/11/26 18:26:20 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	coloring_sprite(int offset_x, int offset_y, int x, int y)
{
	g_data.img_matrix_td[(offset_y + y) *
	g_file.window_w_td + (offset_x + x)] =
	g_texture[4].colors[g_texture[4].color];
}

void	render_sprite(int s_index, int offset_x, int offset_y)
{
	int			x;
	int			y;
	const float	ratio = g_texture[4].width / g_sprites[s_index].scale;

	x = -1;
	while (++x < (int)g_sprites[s_index].scale)
	{
		if (offset_x + x < 0 || offset_x + x >= g_file.window_w_td)
			continue ;
		if (g_rays[offset_x + x].wall_distance <= g_sprites[s_index].distance)
			continue ;
		y = -1;
		g_norm.s_rx = (x * ratio);
		while (++y < (int)g_sprites[s_index].scale)
		{
			if (offset_y + y < 0 || offset_y + y >= g_file.window_h_td)
				continue ;
			g_norm.s_ry = (y * ratio);
			g_texture[4].color = (g_norm.s_ry * g_texture[4].width) +
			g_norm.s_rx;
			if (g_texture[4].colors[g_texture[4].color] !=
				g_texture[4].colors[0])
				coloring_sprite(offset_x, offset_y, x, y);
		}
	}
}

void	sort_sprites(void)
{
	int			i;
	int			j;
	int			sprs_nb;
	t_sprites	spr_tmp;

	i = -1;
	sprs_nb = g_file.number_of_sprites;
	while (++i < g_file.number_of_sprites)
	{
		j = -1;
		while (++j + 1 < sprs_nb)
			if (g_sprites[j].distance < g_sprites[j + 1].distance)
			{
				spr_tmp = g_sprites[j + 1];
				g_sprites[j + 1] = g_sprites[j];
				g_sprites[j] = spr_tmp;
			}
		--sprs_nb;
	}
}

void	draw_sprites(void)
{
	int		i;
	float	pplane_dist;

    g_sprites = (t_sprites *)malloc(sizeof(t_sprites) *
        g_file.number_of_sprites);
    init_sprites();
	pplane_dist = (g_file.window_w_td / 2.0F) / tanf((FOV_ANGLE) / 2);
	i = 0;
	while (i < g_file.number_of_sprites)
	{
		g_sprites[i].distance = distance_between_points(g_sprites[i].x,
		g_sprites[i].y, g_data.px, g_data.py);
		g_sprites[i].angle = atan2f(g_sprites[i].y - g_data.py,
		g_sprites[i].x - g_data.px);
		g_sprites[i].angle = normalize_sprite(g_sprites[i].angle);
		g_sprites[i].scale = (SQUARE / g_sprites[i].distance * pplane_dist);
		g_sprites[i].offset_y = (g_file.window_h_td / 2.0F) -
		(g_sprites[i].scale / 2);
		g_sprites[i].offset_x = (((DEG(g_sprites[i].angle) -
		DEG(g_data.rotation)) * g_file.window_w_td)
		/ (g_texture[4].width) + ((g_file.window_w_td / 2.0F) -
		(g_sprites[i].scale / 2)));
		i++;
	}
	sort_sprites();
	i = -1;
	while (++i < g_file.number_of_sprites)
		render_sprite(i, g_sprites[i].offset_x, g_sprites[i].offset_y);
    free(g_sprites);
}
