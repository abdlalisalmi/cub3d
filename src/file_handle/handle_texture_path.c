/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_texture_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 18:37:57 by aes-salm          #+#    #+#             */
/*   Updated: 2020/11/25 18:33:57 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	path_fill(char *text, char *tmp)
{
	int i;

	i = 0;
	g_file.i += 2;
	while (text[g_file.i] != '.' && text[g_file.i])
		g_file.i++;
	while (text[g_file.i] != '\n' && text[g_file.i])
	{
		tmp[i] = text[g_file.i];
		g_file.i++;
		i++;
	}
}

void	handle_texture_path(char *text)
{
	if (text[g_file.i] == 'N')
		path_fill(text, g_file.no_texture);
	else if (text[g_file.i] == 'S' && text[g_file.i + 1] == 'O')
		path_fill(text, g_file.so_texture);
	else if (text[g_file.i] == 'W')
		path_fill(text, g_file.we_texture);
	else if (text[g_file.i] == 'E')
		path_fill(text, g_file.ea_texture);
	else if (text[g_file.i] == 'S' && text[g_file.i + 1] == ' ')
		path_fill(text, g_file.sprite_texture);
}
