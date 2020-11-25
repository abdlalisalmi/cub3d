/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_resolution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 21:42:49 by aes-salm          #+#    #+#             */
/*   Updated: 2020/11/25 14:27:43 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int		my_atoi(const char *str)
{
	int		result;
	int		sign;

	result = 0;
	sign = 0;
	while (str[file.i] != '\n' && !((str[file.i] >= '0') &&
				(str[file.i] <= '9')) && str[file.i] != '-')
		file.i++;
	sign = (str[file.i] == '-') ? 1 : 0;
	while (str[file.i] == '-' || str[file.i] == '+')
		file.i++;
	while ((str[file.i] >= '0') && (str[file.i] <= '9'))
	{
		result = result * 10;
		result += (int)str[file.i] - '0';
		file.i++;
	}
	return (sign == 1) ? (-result) : result;
}

void	handle_resolution(char *text)
{
	file.window_w_td = my_atoi(text);
	file.window_h_td = my_atoi(text);
	if (file.window_w_td <= 0 || file.window_h_td <= 0)
	{
		write(1, "Error\nThe resolution, should be greater than 0 !!\n", 66);
		exit(EXIT_FAILURE);
	}
	if (file.window_w_td > 2560)
		file.window_w_td = 2560;
	else if (file.window_w_td < 50)
		file.window_w_td = 50;
	if (file.window_h_td > 1800)
		file.window_h_td = 1800;
	else if (file.window_h_td < 50)
		file.window_h_td = 50;
}
