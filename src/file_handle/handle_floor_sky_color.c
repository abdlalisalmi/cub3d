/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_floor_sky_color.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 19:37:36 by aes-salm          #+#    #+#             */
/*   Updated: 2020/11/26 14:56:58 by aes-salm         ###   ########.fr       */
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
	while (str[g_file.i] != '\n' && !((str[g_file.i] >= '0') &&
				(str[g_file.i] <= '9')) && str[g_file.i] != '-')
		g_file.i++;
	sign = (str[g_file.i] == '-') ? 1 : 0;
	while (str[g_file.i] == '-' || str[g_file.i] == '+')
		g_file.i++;
	while ((str[g_file.i] >= '0') && (str[g_file.i] <= '9'))
	{
		value_found = 1;
		result = result * 10;
		result += (int)str[g_file.i] - '0';
		g_file.i++;
	}
	if (value_found < 0)
		return (-1);
	return (sign == 1) ? (-result) : result;
}

int		hexa_to_decimal(char *hexa, int len)
{
	int		base;
	int		dec_val;
	int		i;

	base = 1;
	dec_val = 1;
	i = len - 1;
	while (i >= 0)
	{
		if (hexa[i] >= '0' && hexa[i] <= '9')
		{
			dec_val += (hexa[i] - 48) * base;
			base = base * 16;
		}
		else if (hexa[i] >= 'A' && hexa[i] <= 'F')
		{
			dec_val += (hexa[i] - 55) * base;
			base = base * 16;
		}
		i--;
	}
    free_all(&hexa);
	return (dec_val);
}

int		color_convert(int r, int g, int b)
{
	char	*r_hexa;
	char	*g_hexa;
	char	*b_hexa;
	char	*color;

	r_hexa = convert_to_hexa(r, 'X');
	g_hexa = convert_to_hexa(g, 'X');
	b_hexa = convert_to_hexa(b, 'X');
	color = ft_strjoin(r_hexa, g_hexa);
	color = ft_strjoin(color, b_hexa);
    free_all(&r_hexa);
    free_all(&g_hexa);
    free_all(&b_hexa);
	return (hexa_to_decimal(color, ft_strlen(color)));
}

void	handle_floor_sky_color(char *text)
{
	int		r;
	int		g;
	int		b;
	char	f_c;

	f_c = text[g_file.i];
	r = get_color_value(text);
	g = get_color_value(text);
	b = get_color_value(text);
	if (r < 0 || g < 0 || b < 0)
	{
		write(1, "Error\nthe color RGB code", 26);
		write(1, "should be between 0 and 255 !!\n", 31);
		exit(EXIT_FAILURE);
	}
	if (f_c == 'F')
		g_file.floor_color = color_convert(r, g, b);
	else if (f_c == 'C')
		g_file.sky_color = color_convert(r, g, b);
}
