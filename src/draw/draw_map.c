/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:33:21 by aes-salm          #+#    #+#             */
/*   Updated: 2020/11/25 09:01:16 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int wall_check(float x, float y)
{
    int map_index_X;
    int map_index_Y;

    if (x < 0 || x > (SQUARE * file.num_cols) || y < 0 || y > (SQUARE * file.num_rows))
        return (1);
    map_index_X = floorf(x / SQUARE);
    map_index_Y = floorf(y / SQUARE);

	if (map_index_X > (SQUARE * file.num_cols) || map_index_Y > (SQUARE * file.num_rows))
		return (1);

	if (file.map[map_index_Y][map_index_X] == '1')
		return (1);
    return (0);
}

int sprite_check(float x, float y)
{
    int map_index_X;
    int map_index_Y;

    if (x < 0 || x > (SQUARE * file.num_cols) || y < 0 || y > (SQUARE * file.num_rows))
        return (1);
    map_index_X = floorf(x / SQUARE);
    map_index_Y = floorf(y / SQUARE);

	if (map_index_X > (SQUARE * file.num_cols) || map_index_Y > (SQUARE * file.num_rows))
		return (1);

	if (file.map[map_index_Y][map_index_X] == '2')
		return (1);
    return (0);
}

void    draw_squar(t_struct *data, int x, int y, int color)
{
	int i;
	int j;
	int index;

	j = y;
	while (j < y + SQUARE)
	{
		i = x;
		while (i < x + SQUARE)
		{
			index = (int)(j * (SQUARE * file.num_cols) + i);
			data->img_matrix[index] = color;
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
			color = file.map[j][i] == '1' ? 0xFFFFFF : 0x000000;
			draw_squar(data, x, y,color);
			i++;
		}
		j++;
	}
}
