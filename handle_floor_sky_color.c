/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_floor_sky_color.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 19:37:36 by aes-salm          #+#    #+#             */
/*   Updated: 2020/11/24 19:27:40 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_color_value(const char *str)
{
	int		result;
	int		sign;
    int     value_found;

	result = 0;
	sign = 0;
    value_found = -1;
	while (str[file.i] != '\n' && !((str[file.i] >= '0') &&
				(str[file.i] <= '9')) && str[file.i] != '-')
		file.i++;
	sign = (str[file.i] == '-') ? 1 : 0;
	while (str[file.i] == '-' || str[file.i] == '+')
		file.i++;
	
	while ((str[file.i] >= '0') && (str[file.i] <= '9'))
	{
        value_found = 1;
		result = result * 10;
		result += (int)str[file.i] - '0';
		file.i++;
	}
    if (value_found < 0)
        return (-1);
	return (sign == 1) ? (-result) : result;
}

int hexa_to_decimal(char hexVal[]) 
{    
    int len = strlen(hexVal); 
    int base = 1; 
    int dec_val = 0; 
      
    for (int i=len-1; i>=0; i--) 
    {    
        if (hexVal[i]>='0' && hexVal[i]<='9') 
        { 
            dec_val += (hexVal[i] - 48)*base; 
            base = base * 16; 
        } 
        else if (hexVal[i]>='A' && hexVal[i]<='F') 
        { 
            dec_val += (hexVal[i] - 55)*base; 
            base = base*16; 
        } 
    } 
    return dec_val; 
} 

int    color_convert(int r, int g, int b)
{
	char *r_hexa;
	char *g_hexa;
	char *b_hexa;
	char *color;

    r_hexa = convert_to_hexa(r, 'X');
	g_hexa = convert_to_hexa(g, 'X');
	b_hexa = convert_to_hexa(b, 'X');
	color = ft_strjoin(r_hexa, g_hexa);
	color = ft_strjoin(color, b_hexa);
    return (hexa_to_decimal(color));
}

void    handle_floor_sky_color(char *text)
{
	int r;
    int g;
    int b;
	char f_c;

	f_c = text[file.i];
    r = get_color_value(text);
    g = get_color_value(text);
    b = get_color_value(text);
    if (r < 0 || g < 0 || b < 0)
    {
        write(1, "Error\nthe color RGB code should be between 0 and 255 !!\n", 56);
        exit(EXIT_FAILURE);
    }
    printf("r: %d\n", r);
    printf("g: %d\n", g);
    printf("b: %d\n", b);
    if (f_c == 'F')
       file.floor_color = color_convert(r, g ,b);
    else if (f_c == 'C')
       file.sky_color = color_convert(r, g ,b);
}
