/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 14:15:44 by aes-salm          #+#    #+#             */
/*   Updated: 2020/11/27 09:30:13 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	get_player_position(char c, int row, int col)
{
	g_file.player_found++;
	g_file.px = row;
	g_file.py = col;
	if (c == 'N')
		g_file.player_view = 0.665;
	if (c == 'W')
		g_file.player_view = 1;
	if (c == 'S')
		g_file.player_view = 2;
	if (c == 'E')
		g_file.player_view = 60;
}

void	handle_map_line(char *line, int row, int i)
{
	g_file.map[row] = ft_memset(g_file.map[row], '.', g_file.num_cols + 1);
	while (line[i])
	{
		if (line[i] == '2')
			g_file.number_of_sprites++;
		if (line[i] != 'N' && line[i] != 'W' && line[i] != 'S' &&
		line[i] != 'E' && line[i] != '1' && line[i] != '0' &&
		line[i] != '2' && line[i] != ' ')
		{
			write(1, "Error:\nBad character in the map in position X=", 47);
			ft_putnbr(row + 1);
			write(1, " Y=", 3);
			ft_putnbr(i + 2);
			write(1, "\n", 1);
			exit_cub(EXIT_FAILURE);
		}
		if (line[i] == 'N' || line[i] == 'W' ||
		line[i] == 'S' || line[i] == 'E')
			get_player_position(line[i], row, i);
		if (line[i] != ' ')
			g_file.map[row][i] = line[i];
		i++;
	}
	g_file.map[row][g_file.num_cols] = '\0';
}

void	handle_map(char *line, int row)
{
	if (line[0] == ' ' || line[0] == '1')
	{
		handle_map_line(line, row, 0);
		g_file.row++;
	}
	else if (line[0] == '\t')
	{
		write(1, "Error\nYou are not allowed", 25);
		write(1, " to add tabs on the map file. !!\n", 33);
		free_all(&line);
		exit(EXIT_FAILURE);
	}
	free_all(&line);
}
