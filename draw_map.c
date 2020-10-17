/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:33:21 by aes-salm          #+#    #+#             */
/*   Updated: 2020/10/17 14:29:35 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int wall_check(float x, float y)
{
    int map_index_X;
    int map_index_Y;

    if (x < 0 || x > (SQUARE * file.num_cols) || y < 0 || y > (SQUARE * file.num_rows))
        return (1);
    map_index_X = floorf(x / SQUARE);
    map_index_Y = floorf(y / SQUARE);
    return (file.map[map_index_Y][map_index_X]);
}

void    draw_squar(t_struct *data, int x, int y, int color)
{
	int i;
	int j;
	j = y;
	while (j < y + SQUARE)
	{
		i = x;
		while (i < x + SQUARE)
		{
			data->img_matrix[((int)j * (SQUARE * file.num_cols) + (int)i)] = color;
			i++;
		}
		j++;
	}
}

void draw_map(t_struct *data)
{
	int color;
	int	i;
	int	j;
	int	x;
	int	y;

	j = 0;
	while (j < file.num_rows)
	{
		i = 0;
		while (i < file.num_cols)
		{
			x = i * SQUARE;
			y = j * SQUARE;
			color = file.map[j][i] == 1 ? 0xFFFFFF : 0x000000;
			draw_squar(data, x, y,color);
			i++;
		}
		j++;
	}
}
