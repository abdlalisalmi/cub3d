/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 11:54:56 by aes-salm          #+#    #+#             */
/*   Updated: 2020/03/13 21:57:01 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	file_handle()
{
	int i;
	int fd;
	char data[1024];

	file.i = 0;
	i = 0;
	while (i++ <= 1024)
		data[i] = 0;

	fd = open("./text.cub", O_RDONLY);
	read(fd , data, 1024);
	close(fd);
	while (data[file.i])
	{
		if (data[file.i] == 'R')
		{
			handle_resolution(data);
			break;
		}
		file.i++;
	}
}
