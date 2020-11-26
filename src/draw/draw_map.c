/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:33:21 by aes-salm          #+#    #+#             */
/*   Updated: 2020/11/25 18:31:21 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int		wall_check(float x, float y)
{
	int map_index_x;
	int map_index_y;

	if (x < 0 || x > (SQUARE * g_file.num_cols) || y < 0 ||
	y > (SQUARE * g_file.num_rows))
		return (1);
	map_index_x = floorf(x / SQUARE);
	map_index_y = floorf(y / SQUARE);
	if (map_index_x > (SQUARE * g_file.num_cols) ||
	map_index_y > (SQUARE * g_file.num_rows))
		return (1);
	if (g_file.map[map_index_y][map_index_x] == '1')
		return (1);
	return (0);
}

int		sprite_check(float x, float y)
{
	int map_index_x;
	int map_index_y;

	if (x < 0 || x > (SQUARE * g_file.num_cols) ||
	y < 0 || y > (SQUARE * g_file.num_rows))
		return (1);
	map_index_x = floorf(x / SQUARE);
	map_index_y = floorf(y / SQUARE);
	if (map_index_x > (SQUARE * g_file.num_cols) ||
	map_index_y > (SQUARE * g_file.num_rows))
		return (1);
	if (g_file.map[map_index_y][map_index_x] == '2')
		return (1);
	return (0);
}

void	draw_squar(t_struct *g_data, int x, int y, int color)
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
			index = (int)(j * (SQUARE * g_file.num_cols) + i);
			g_data->img_matrix[index] = color;
			i++;
		}
		j++;
	}
}

void	draw_map(t_struct *g_data)
{
	int color;
	int	i;
	int	j;
	int	x;
	int	y;

	j = 0;
	while (j < g_file.num_rows)
	{
		i = 0;
		while (i < g_file.num_cols)
		{
			x = i * SQUARE;
			y = j * SQUARE;
			color = g_file.map[j][i] == '1' ? 0xFFFFFF : 0x000000;
			draw_squar(g_data, x, y, color);
			i++;
		}
		j++;
	}
}
