/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 11:55:04 by aes-salm          #+#    #+#             */
/*   Updated: 2020/10/26 13:41:49 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void render_sprite(int s_index, int offsetX, int offsetY)
{
    int			x;
	int			y;
	int			rx;
	int			ry;
	const float	ratio = texture[4].width / sprites[s_index].scale;

	x = -1;
	while (++x < (int)sprites[s_index].scale)
	{
		if (offsetX + x < 0 || offsetX + x >= file.window_w_td)
			continue ;
		if (rays[offsetX + x].wall_distance <= sprites[s_index].distance)
			continue ;
		y = -1;
		rx = (x * ratio);
		while (++y < (int)sprites[s_index].scale)
		{
			if (offsetY + y < 0 || offsetY + y >= file.window_h_td)
				continue ;
			ry = (y * ratio);
			texture[4].color = (ry * texture[4].width) + rx;
			if (texture[4].colors[texture[4].color] != texture[4].colors[0])
				data->img_matrix_td[(offsetY + y) * file.window_w_td + (offsetX + x)] = texture[4].colors[texture[4].color];
		}
	}
}

void	sort_sprites()
{
    int i;
	int	j;
    int sprs_nb;
    t_sprites spr_tmp;

	i = -1;
	sprs_nb = file.number_of_sprites;
    while (++i < file.number_of_sprites)
    {
		j = -1;
        while (++j + 1 < sprs_nb)
            if (sprites[j].distance < sprites[j + 1].distance)
            {
                spr_tmp = sprites[j + 1];
                sprites[j + 1] = sprites[j];
                sprites[j] = spr_tmp;
            }
        --sprs_nb;
    }
}

void draw_sprites()
{
    int i;
    float pplane_dist;

    pplane_dist = (file.window_w_td / 2.0F) / tanf((FOV_ANGLE) / 2);
    i = 0;
    while (i < file.number_of_sprites)
    {
        sprites[i].distance = distance_between_points(sprites[i].x, sprites[i].y, data->px, data->py);
		sprites[i].angle = atan2f(sprites[i].y - data->py,
								 sprites[i].x - data->px);
		sprites[i].angle = normalize_sprite(sprites[i].angle);
		sprites[i].scale = (SQUARE / sprites[i].distance * pplane_dist);
		sprites[i].offsetY = (file.window_h_td / 2.0F) - (sprites[i].scale / 2);
		sprites[i].offsetX = (((DEG(sprites[i].angle) - DEG(data->rotation)) * file.window_w_td)
		/ (texture[4].width) + ((file.window_w_td / 2.0F) - (sprites[i].scale / 2)));
        i++;
    }
	sort_sprites();
    i = -1;
	while (++i < file.number_of_sprites)
		render_sprite(i, sprites[i].offsetX, sprites[i].offsetY);
}