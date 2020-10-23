/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 11:54:56 by aes-salm          #+#    #+#             */
/*   Updated: 2020/10/23 09:53:02 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void get_map_ready(char *cub_file)
{
	int i;
	int fd;
	char *line;

    i = 0;
    file.map = (char **)malloc((file.num_rows) * sizeof(char*));
    while (i < file.num_rows)
        file.map[i++] = (char *)malloc((file.num_cols + 1) * sizeof(char));
	file.row = 0;
	fd = open(cub_file, O_RDONLY);
    while (get_next_line(fd, &line))
		handle_map(line, file.row);
	handle_map(line, file.row - 1);
	close(fd);
	if (file.player_found == 0)
	{
		write(1, "Error:\nYou don't have any player in the MAP or you dont have a MAP !!\n",72);
        exit_cub(EXIT_FAILURE);
	}
	handle_map_error();
}

void	text_handle(char *data)
{
	while (data[file.i])
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
