/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 11:54:56 by aes-salm          #+#    #+#             */
/*   Updated: 2020/11/26 14:42:03 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	get_map_ready(char *cub_file)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	g_file.map = (char **)malloc((g_file.num_rows) * sizeof(char*));
	while (i < g_file.num_rows)
		g_file.map[i++] = (char *)malloc((g_file.num_cols + 1) * sizeof(char));
	g_file.row = 0;
	fd = open(cub_file, O_RDONLY);
	while (get_next_line(fd, &line))
		handle_map(line, g_file.row);
	handle_map(line, g_file.row - 1);
	close(fd);
	if (g_file.player_found == 0)
	{
		write(1, "Error:\nYou don't have any player in the MAP!!\n", 72);
		exit_cub(EXIT_FAILURE);
	}
	handle_map_error();
}

void	text_handle(char *text)
{
	while (text[g_file.i])
	{
		if (text[g_file.i] == 'R')
			handle_resolution(text);
		if (text[g_file.i] == 'N' || (text[g_file.i] == 'S' &&
			text[g_file.i + 1] == 'O') ||
			text[g_file.i] == 'W' || text[g_file.i] == 'E' ||
			(text[g_file.i] == 'S' && text[g_file.i + 1] == ' '))
			handle_texture_path(text);
		if (text[g_file.i] == 'F' || text[g_file.i] == 'C')
			handle_floor_sky_color(text);
		g_file.i++;
	}
}

void	file_handle(char *cub_file)
{
	int		fd;
	char	*text;
	char	*line;

	text = malloc(sizeof(char) * BUFFER_SIZE);
	g_file.i = 0;
	fd = open(cub_file, O_RDONLY);
	read(fd, text, BUFFER_SIZE);
	text_handle(text);
    free(text);
	g_file.num_rows = 0;
	g_file.num_cols = 0;
	fd = open(cub_file, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		if (line[0] == ' ' || line[0] == '1')
		{
			g_file.num_rows++;
			if ((unsigned int)g_file.num_cols < get_strlen(line))
				g_file.num_cols = get_strlen(line);
		}
		free_all(&line);
	}
	free_all(&line);
	close(fd);
	get_map_ready(cub_file);
}
