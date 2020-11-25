/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 14:17:27 by aes-salm          #+#    #+#             */
/*   Updated: 2020/05/06 rows:05:52 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int is_map_opened(int x, int y, int rows, int cols, char new_map[rows][cols])
{
	char el;

	if (x < 0 || x == rows || y < 0 || y == cols)
		return (0);
	el = new_map[x][y];
	if (el != '.' && el != '1')
	{
		write(1, "Error:\nThe map is opened in X=",30);
		ft_putnbr(x);
		write(1, " Y=",3);
		ft_putnbr(y);
		write(1, "\n",1);
		exit_cub(EXIT_FAILURE);
	}
	new_map[x][y] = '1';
	if (el == '.')
	{
		is_map_opened(x, y + 1, rows, cols, new_map);
		is_map_opened(x, y - 1, rows, cols, new_map);
		is_map_opened(x + 1, y, rows, cols, new_map);
		is_map_opened(x - 1, y, rows, cols, new_map);
		is_map_opened(x + 1, y + 1, rows, cols, new_map);
		is_map_opened(x + 1, y - 1, rows, cols, new_map);
		is_map_opened(x - 1, y - 1, rows, cols, new_map);
		is_map_opened(x - 1, y + 1, rows, cols, new_map);
	}
	return (1);
}

static void	create_new_map()
{
	int rows = file.num_rows + 2;
	int cols = file.num_cols + 2;
	char new_map[rows][cols];
	int x;
	int y;

	x = 0;
	y = 0;

	while (x < rows)
	{
		y = 0;
		while (y < cols)
		{
			if (x == 0 || x == rows - 1)
				new_map[x][y] = '.';
			else if (y == 0 || y == cols - 1)
				new_map[x][y] = '.';
			else
				new_map[x][y] = file.map[x-1][y-1];
			y++;
		}
		x++;
	}
	is_map_opened(0, 0, rows, cols, new_map);
}


void handle_map_error()
{
	create_new_map();
}