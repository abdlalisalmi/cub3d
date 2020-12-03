/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 11:54:56 by aes-salm          #+#    #+#             */
/*   Updated: 2020/12/03 11:36:08 by aes-salm         ###   ########.fr       */
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
	handle_map(line, g_file.row);
	close(fd);
	if (g_file.player_found == 0)
	{
		print_errors("You don't have any player or MAP");
	}
	handle_map_error();
}

void	text_handle(char *text)
{
	g_file.map_tour = 0;
	while (text[g_file.i])
	{
		if (text[g_file.i] == 'R')
		{
			handle_resolution(text);
			g_file.map_tour++;
		}
		else if ((text[g_file.i] == 'N' && text[g_file.i + 1] == 'O') ||
            (text[g_file.i] == 'S' && text[g_file.i + 1] == 'O') ||
			(text[g_file.i] == 'W' && text[g_file.i + 1] == 'E') ||
			(text[g_file.i] == 'E' && text[g_file.i + 1] == 'A') ||
			(text[g_file.i] == 'S' && text[g_file.i + 1] == ' '))
		{
			handle_texture_path(text);
			g_file.map_tour++;
		}
		else if (text[g_file.i] == 'F' || text[g_file.i] == 'C')
		{
			handle_floor_sky_color(text);
			g_file.map_tour++;
		}
		else if (g_file.map_tour < 8 && (text[g_file.i] != 'R' &&
			text[g_file.i] != 'N' && text[g_file.i] != 'S' &&
			text[g_file.i] != 'W' && text[g_file.i] != 'E' &&
			text[g_file.i] != 'F' && text[g_file.i] != 'C' &&
			text[g_file.i] != '\n'))
		{
			free(text);
			print_errors("A weird or missing element in the map file!");
		}
		g_file.i++;
	}
}

void	rows_and_cols_calc(char *cub_file)
{
	char	*line;
	int		fd;

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
	g_file.num_rows++;
	if ((unsigned int)g_file.num_cols < get_strlen(line))
		g_file.num_cols = get_strlen(line);
	free_all(&line);
	close(fd);
}

void	file_handle(char *cub_file)
{
	int		fd;
	char	*text;

	text = malloc(sizeof(char) * BUFFER_SIZE);
	g_file.i = 0;
	fd = open(cub_file, O_RDONLY);
	if (fd == -1)
	{
		print_errors("Unable to open the map file");
		free(text);
	}
	read(fd, text, BUFFER_SIZE);
	text_handle(text);
	free(text);
	close(fd);
	rows_and_cols_calc(cub_file);
	get_map_ready(cub_file);
}
