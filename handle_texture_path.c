/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_texture_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 18:37:57 by aes-salm          #+#    #+#             */
/*   Updated: 2020/10/16 14:01:20 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	path_fill(char *data, char *tmp)
{
	int i;

	i = 0;
	file.i += 2;
	while (data[file.i] != '.')
		file.i++;
	while (data[file.i] != '\n')
	{
		tmp[i] = data[file.i];
		file.i++;
		i++;
	}
}

void    handle_texture_path(char *data)
{
	file.map_tour++;
	if (data[file.i] == 'N')
		path_fill(data, file.no_texture);
	else if (data[file.i] == 'S' && data[file.i + 1] == 'O')
		path_fill(data, file.so_texture);
	else if (data[file.i] == 'W')
		path_fill(data, file.we_texture);
	else if (data[file.i] == 'E')
		path_fill(data, file.ea_texture);
	else if (data[file.i] == 'S' && data[file.i + 1] == ' ')
		path_fill(data, file.sprite_texture);
}
