/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_resolution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 21:42:49 by aes-salm          #+#    #+#             */
/*   Updated: 2020/12/11 13:07:21 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int		get_value(const char *str)
{
	int		result;
	int		sign;

	result = 0;
	sign = 0;
	while (str[g_file.i] != '\n' && str[g_file.i] == ' ')
		g_file.i++;
	sign = (str[g_file.i] == '-') ? 1 : 0;
	while (str[g_file.i] == '-' || str[g_file.i] == '+')
		g_file.i++;
	while (str[g_file.i] != ' ' && str[g_file.i] != '\n')
	{
		if (!(str[g_file.i] >= '0' && str[g_file.i] <= '9'))
			print_errors("Wrong value in the Resolution");
		result = result * 10;
		result += (int)str[g_file.i] - '0';
		if (result >= 20000)
			g_file.max_int = 1;
		g_file.i++;
	}
	while (str[g_file.i] == ' ')
		g_file.i++;
	if (g_file.max_int)
		return (g_file.max_int && sign) ? (-20000) : (20000);
	return (sign == 1) ? (-result) : result;
}

void	handle_resolution(char *text)
{
	g_file.map_tour++;
	if (g_file.window_w_td != 0 && g_file.window_w_td != 0)
		print_errors("Duplicate elemant R");
	g_file.i++;
	g_file.window_w_td = get_value(text);
	g_file.window_h_td = get_value(text);
	if (g_file.window_w_td <= 0 || g_file.window_h_td <= 0)
		print_errors("The resolution, should be greater than 0");
	if (g_file.window_w_td > 2560)
		g_file.window_w_td = 2560;
	if (g_file.window_h_td > 1800)
		g_file.window_h_td = 1800;
}
