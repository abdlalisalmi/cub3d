/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 14:15:44 by aes-salm          #+#    #+#             */
/*   Updated: 2020/10/21 14:30:59 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void get_player_position(char c, int row, int col)
{
		file.px = row;
        file.py = col;
	    if (c == 'N')
			file.player_view = 0.665;
		if (c == 'W')
			file.player_view = 1;
		if (c == 'S')
			file.player_view = 2;
		if (c == 'E')
			file.player_view = 60;

}

void    handle_map_line(char *line, int row)
{
    int i;

    file.map[row] = ft_memset(file.map[row], '.', file.num_cols + 1);
    i = 0;
    while (i < file.num_cols && line[i])
    {
        if (line[i] == 'N' || line[i] == 'W' || line[i] == 'S' || line[i] == 'E')
			get_player_position(line[i], row, i);
        if (line[i] != ' ')
            file.map[row][i] = line[i];
        i++;
    }
    file.map[row][file.num_cols] = '\0';
}

void handle_map(char *line, int row)
{
    if (line[0] == ' ' || line[0] == '1')
    {
        handle_map_line(line, row);
        file.row++;
    }
    else if (line[0] == '\t')
    {
        write(1, "Error\nYou are not allowed to add tabs on the map file. !!\n", 58);
        free_all(&line);
        exit(EXIT_FAILURE);
    }
    free_all(&line);
}