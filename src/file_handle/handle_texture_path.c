/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_texture_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 18:37:57 by aes-salm          #+#    #+#             */
/*   Updated: 2020/11/25 14:29:10 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	path_fill(char *text, char *tmp)
{
	int i;

	i = 0;
	file.i += 2;
	while (text[file.i] != '.' && text[file.i])
		file.i++;
	while (text[file.i] != '\n' && text[file.i])
	{
		tmp[i] = text[file.i];
		file.i++;
		i++;
	}
}

void	handle_texture_path(char *text)
{
	if (text[file.i] == 'N')
		path_fill(text, file.no_texture);
	else if (text[file.i] == 'S' && text[file.i + 1] == 'O')
		path_fill(text, file.so_texture);
	else if (text[file.i] == 'W')
		path_fill(text, file.we_texture);
	else if (text[file.i] == 'E')
		path_fill(text, file.ea_texture);
	else if (text[file.i] == 'S' && text[file.i + 1] == ' ')
		path_fill(text, file.sprite_texture);
}
