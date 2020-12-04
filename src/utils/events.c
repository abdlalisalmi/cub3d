/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:11:33 by aes-salm          #+#    #+#             */
/*   Updated: 2020/12/04 18:05:28 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int		keypress(int keycode)
{
	if (keycode == W || keycode == UP)
		g_data.walk_direction = 1;
	else if (keycode == S || keycode == DOWN)
		g_data.walk_direction = -1;
	else if (keycode == RIGHT)
		g_data.turn_direction = 1;
	else if (keycode == LEFT)
		g_data.turn_direction = -1;
	else if (keycode == A)
	{
		g_data.side = -(PI / 2);
		g_data.walk_direction = 1;
	}
	else if (keycode == D)
	{
		g_data.side = PI / 2;
		g_data.walk_direction = 1;
	}
	else if (keycode == ESC)
		exit_cub(EXIT_SUCCESS);
	return (0);
}

int		keyrelease(int keycode)
{
	if (keycode == W || keycode == UP)
		g_data.walk_direction = 0;
	else if (keycode == S || keycode == DOWN)
		g_data.walk_direction = 0;
	else if (keycode == RIGHT)
		g_data.turn_direction = 0;
	else if (keycode == LEFT)
		g_data.turn_direction = 0;
	else if (keycode == A || keycode == D)
	{
		g_data.side = 0;
		g_data.walk_direction = 0;
	}
	return (0);
}
