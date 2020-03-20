/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_resolution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 21:42:49 by aes-salm          #+#    #+#             */
/*   Updated: 2020/03/17 16:01:58 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	my_atoi(const char *str)
{
	int	result;

	result = 0;
	while (str[file.i] != '\n' && !((str[file.i] >= '0') && (str[file.i] <= '9')))
		file.i++;
	while ((str[file.i] >= '0') && (str[file.i] <= '9'))
	{
		result = result * 10;
		result += (int)str[file.i] - '0';
		file.i++;
	}
	return (result);
}

void	handle_resolution(char *data)
{
	file.map_tour++;
	file.window_w_td = my_atoi(data);
	file.window_h_td = my_atoi(data);
}
