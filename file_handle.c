/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 11:54:56 by aes-salm          #+#    #+#             */
/*   Updated: 2020/10/21 11:57:49 by aes-salm         ###   ########.fr       */
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

void get_map_ready(char *cub_file)
{
	int i;
	int fd;
	char *line;

    i = 0;
    file.map = (char **)malloc((file.num_rows) * sizeof(char*));
    while (i < file.num_rows)
        file.map[i++] = (char *)malloc((file.num_cols + 1) * sizeof(char));
	i = 0;
	fd = open(cub_file, O_RDONLY);
    while (get_next_line(fd, &line))
    {
		if (line[0] == ' ' || line[0] == '1')
		{
			handle_map_line(line, i);
			i++;
		}
		if (line[0] == '\t')
		{
			write(1, "Error\nYou are not allowed to add tabs on the map file. !!\n", 58);
			free_all(&line);
        	exit(EXIT_FAILURE);
		}
        free_all(&line);
    }
	if (line[0] == ' ' || line[0] == '1')
		handle_map_line(line, file.num_rows - 1);
    free_all(&line);
	close(fd);
	handle_map_error();
}

void	text_handle(char *data)
{
	file.map_tour = 0;
	while (file.map_tour < 8)
	{
		if (data[file.i] == 'R')
			handle_resolution(data);
		if (data[file.i] == 'N' || (data[file.i] == 'S' && data[file.i + 1] == 'O') ||
				 data[file.i] == 'W' || data[file.i] == 'E' ||
				 (data[file.i] == 'S' && data[file.i + 1] == ' '))
			handle_texture_path(data);
		if (data[file.i] == 'F' || data[file.i] == 'C')
			handle_floor_sky_color(data);
		file.i++;
	}
}

void	file_handle(char *cub_file)
{
	int fd;
	char *data;
    char *line;

	data = malloc(sizeof(char) * BUFFER_SIZE);
	file.i = 0;
	fd = open(cub_file, O_RDONLY);
	read(fd , data, BUFFER_SIZE);
	text_handle(data);

	file.num_rows = 0;
	file.num_cols = 0;
	fd = open(cub_file, O_RDONLY);
	while (get_next_line(fd, &line))
    {
		if (line[0] == ' ' || line[0] == '1')
		{
			file.num_rows++;
			if ((unsigned int)file.num_cols < get_strlen(line))
				file.num_cols = get_strlen(line);
		}
        free_all(&line);
    }
    free_all(&line);
	close(fd);
	get_map_ready(cub_file);
}
