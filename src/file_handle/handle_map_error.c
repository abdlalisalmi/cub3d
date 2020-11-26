/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 14:17:27 by aes-salm          #+#    #+#             */
/*   Updated: 2020/11/25 18:40:12 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	error_found(int y, int x)
{
	write(1, "Error:\nThe map is opened in X=", 30);
	ft_putnbr(x);
	write(1, " Y=", 3);
	ft_putnbr(y);
	write(1, "\n", 1);
	exit_cub(EXIT_FAILURE);
}

int		is_map_opened(int x, int y, char new_map[g_norm.rows][g_norm.cols])
{
	char el;

	if (x < 0 || x == g_norm.rows || y < 0 || y == g_norm.cols)
		return (0);
	el = new_map[x][y];
	if (el != '.' && el != '1')
		error_found(x, y);
	new_map[x][y] = '1';
	if (el == '.')
	{
		is_map_opened(x, y + 1, new_map);
		is_map_opened(x, y - 1, new_map);
		is_map_opened(x + 1, y, new_map);
		is_map_opened(x - 1, y, new_map);
		is_map_opened(x + 1, y + 1, new_map);
		is_map_opened(x + 1, y - 1, new_map);
		is_map_opened(x - 1, y - 1, new_map);
		is_map_opened(x - 1, y + 1, new_map);
	}
	return (1);
}

void	create_new_map(void)
{
	char	new_map[g_norm.rows][g_norm.cols];
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (x < g_norm.rows)
	{
		y = 0;
		while (y < g_norm.cols)
		{
			if (x == 0 || x == g_norm.rows - 1)
				new_map[x][y] = '.';
			else if (y == 0 || y == g_norm.cols - 1)
				new_map[x][y] = '.';
			else
				new_map[x][y] = g_file.map[x - 1][y - 1];
			y++;
		}
		x++;
	}
	is_map_opened(0, 0, new_map);
}

void	handle_map_error(void)
{
	g_norm.rows = g_file.num_rows + 2;
	g_norm.cols = g_file.num_cols + 2;
	create_new_map();
}
