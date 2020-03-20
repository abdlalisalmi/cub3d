/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_floor_sky_color.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 19:37:36 by aes-salm          #+#    #+#             */
/*   Updated: 2020/03/17 16:02:30 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

const int    color_convert(int r, int g, int b)
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
	// color[0] = r_hexa[0];
	// color[1] = r_hexa[1];
	// color[2] = g_hexa[0];
	// color[3] = g_hexa[1];
	// color[4] = b_hexa[0];
	// color[5] = b_hexa[1];

    return (hexa_to_decimal(color));
}

void    handle_floor_sky_color(char *data)
{
	int r;
    int g;
    int b;
	char f_c;

	file.map_tour++;
	f_c = data[file.i];
    r = my_atoi(data);
    g = my_atoi(data);
    b = my_atoi(data);
    if (f_c == 'F')
       file.floor_color = color_convert(r, g ,b);
    else if (f_c == 'C')
       file.sky_color = color_convert(r, g ,b);
}
