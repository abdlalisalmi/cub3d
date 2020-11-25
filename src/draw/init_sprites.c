/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 12:23:00 by aes-salm          #+#    #+#             */
/*   Updated: 2020/11/25 11:48:23 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	handle_sprite_position(int i, int j, int sprite_index)
{
	sprites[sprite_index].x = (j + 0.5f) * SQUARE;
	sprites[sprite_index].y = (i + 0.5f) * SQUARE;
}

void	init_sprites(void)
{
	int i;
	int j;
	int sprite_index;

	i = 0;
	sprite_index = 0;
	while (i < file.num_rows)
	{
		j = 0;
		while (j < file.num_cols)
		{
			if (file.map[i][j] == '2')
			{
				handle_sprite_position(i, j, sprite_index);
				sprite_index++;
			}
			j++;
		}
		i++;
	}
}
