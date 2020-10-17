/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 11:54:56 by aes-salm          #+#    #+#             */
/*   Updated: 2020/10/16 19:00:53 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	text_handle(char *data)
{
	file.map_tour = 0;
	while (file.map_tour < 9)
	{
		if (data[file.i] == 'R')
			handle_resolution(data);
		if (data[file.i] == 'N' || (data[file.i] == 'S' && data[file.i + 1] == 'O') ||
				 data[file.i] == 'W' || data[file.i] == 'E' ||
				 (data[file.i] == 'S' && data[file.i + 1] == ' '))
			handle_texture_path(data);
		if (data[file.i] == 'F' || data[file.i] == 'C')
			handle_floor_sky_color(data);
		if (file.map_tour == 8)
		{
			file.map_tour++;
			handle_map(data);
		}
		file.i++;
	}
}

void	file_handle(char *cub_file)
{
	int fd;
	char data[1024];

	file.i = 0;
	fd = open(cub_file, O_RDONLY);
	read(fd , data, 1024);
	text_handle(data);
	close(fd);
}
