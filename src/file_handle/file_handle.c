/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 11:54:56 by aes-salm          #+#    #+#             */
/*   Updated: 2020/11/25 11:58:58 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	get_map_ready(char *cub_file)
{
	int		i;
	int		fd;
	char	*line;

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
		write(1, "Error:\nYou don't have any player in the MAP!!\n", 72);
		exit_cub(EXIT_FAILURE);
	}
	handle_map_error();
}

void	text_handle(char *text)
{
	while (text[file.i])
	{
		if (text[file.i] == 'R')
			handle_resolution(text);
		if (text[file.i] == 'N' || (text[file.i] == 'S' &&
			text[file.i + 1] == 'O') ||
			text[file.i] == 'W' || text[file.i] == 'E' ||
			(text[file.i] == 'S' && text[file.i + 1] == ' '))
			handle_texture_path(text);
		if (text[file.i] == 'F' || text[file.i] == 'C')
			handle_floor_sky_color(text);
		file.i++;
	}
}

void	file_handle(char *cub_file)
{
	int		fd;
	char	*text;
	char	*line;

	text = malloc(sizeof(char) * BUFFER_SIZE);
	file.i = 0;
	fd = open(cub_file, O_RDONLY);
	read(fd, text, BUFFER_SIZE);
	text_handle(text);
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
