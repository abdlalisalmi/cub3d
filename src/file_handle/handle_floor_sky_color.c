/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_floor_sky_color.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 19:37:36 by aes-salm          #+#    #+#             */
/*   Updated: 2020/12/07 11:24:24 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int		get_color_value(const char *str)
{
	int		result;
	int		sign;
	int		value_found;

	result = 0;
	sign = 0;
	value_found = -1;
	while (str[g_file.i] != '\n' &&
		(str[g_file.i] == ' ' || str[g_file.i] == ','))
		g_file.i++;
	sign = (str[g_file.i] == '-') ? 1 : 0;
	while (str[g_file.i] == '-' || str[g_file.i] == '+')
		g_file.i++;
	while (str[g_file.i] != ',' && str[g_file.i] != '\n')
	{
		if (!(str[g_file.i] >= '0' && str[g_file.i] <= '9'))
			print_errors("Wrong value in the floor or the sky");
		value_found = 1;
		result = result * 10;
		result += (int)str[g_file.i] - '0';
		g_file.i++;
	}
	if (value_found < 0)
		return (-1);
	return (sign == 1) ? (-result) : result;
}

int		color_convert(int r, int g, int b)
{
	int	result;

	result = (r * 256 * 256) + (g * 256) + b;
	return (result);
}

void	handle_floor_sky_color(char *text)
{
	char	f_c;

	g_file.map_tour++;
	f_c = text[g_file.i];
	g_file.i++;
	if (text[g_file.i] != ' ')
		print_errors("We need more space, please");
	g_file.r = get_color_value(text);
	g_file.g = get_color_value(text);
	g_file.b = get_color_value(text);
	if ((g_file.r < 0 || g_file.r > 255) || (g_file.g < 0 ||
		g_file.g > 255) || (g_file.b < 0 || g_file.b > 255))
		print_errors("RGB code should be between 0 and 255");
	if (f_c == 'F')
	{
		if (g_file.floor_color != 0)
			print_errors("Duplicate F elemant");
		g_file.floor_color = color_convert(g_file.r, g_file.g, g_file.b);
	}
	else if (f_c == 'C')
	{
		if (g_file.sky_color != 0)
			print_errors("Duplicate C elemant");
		g_file.sky_color = color_convert(g_file.r, g_file.g, g_file.b);
	}
}
