/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_texture_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 18:37:57 by aes-salm          #+#    #+#             */
/*   Updated: 2020/12/05 10:50:01 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	path_fill(char *text, char *tmp, int pas)
{
	int		i;

	i = 0;
	g_file.i += pas;
	if (text[g_file.i] != ' ')
		tmp = NULL;
	else
	{
		while (text[g_file.i] == ' ' && text[g_file.i])
			g_file.i++;
		while (text[g_file.i] != '\n' && text[g_file.i])
		{
			tmp[i] = text[g_file.i];
			g_file.i++;
			i++;
		}
		i = ft_strlen(tmp) - 1;
		while (i >= 0 && tmp[i] == ' ')
		{
			tmp[i] = 0;
			i--;
		}
	}
}

void	duplicate_element(char *path)
{
	if (path[0] != '\0')
		print_errors("Duplicate PATH elemant");
}

void	handle_texture_path_part2(char *text)
{
	duplicate_element(g_file.sprite_texture);
	path_fill(text, g_file.sprite_texture, 1);
}

void	handle_texture_path(char *text)
{
	g_file.map_tour++;
	if (text[g_file.i] == 'N')
	{
		duplicate_element(g_file.no_texture);
		path_fill(text, g_file.no_texture, 2);
	}
	else if (text[g_file.i] == 'S' && text[g_file.i + 1] == 'O')
	{
		duplicate_element(g_file.so_texture);
		path_fill(text, g_file.so_texture, 2);
	}
	else if (text[g_file.i] == 'W')
	{
		duplicate_element(g_file.we_texture);
		path_fill(text, g_file.we_texture, 2);
	}
	else if (text[g_file.i] == 'E')
	{
		duplicate_element(g_file.ea_texture);
		path_fill(text, g_file.ea_texture, 2);
	}
	else if (text[g_file.i] == 'S' && text[g_file.i + 1] == ' ')
		handle_texture_path_part2(text);
}
