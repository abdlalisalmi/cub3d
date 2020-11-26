/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bmp_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 11:10:48 by aes-salm          #+#    #+#             */
/*   Updated: 2020/11/26 14:46:02 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

t_rgb	*g_rgb;

void	screenshot_error(char *message)
{
	write(1, "Error:\n", 8);
	write(1, message, ft_strlen(message));
	write(1, "\n", 1);
	exit_cub(EXIT_FAILURE);
}

void	color_converter(int hex_value)
{
	if (!(g_rgb = malloc(sizeof(t_rgb))))
		screenshot_error("failed to alloc the RGB colors !!");
	g_rgb->r = (hex_value / pow(2, 16));
	g_rgb->g = (hex_value / pow(2, 8));
	g_rgb->b = (hex_value);
}

void	screen_data(int x)
{
	int index;

	index = g_bitmap.row * g_file.window_w_td + g_bitmap.col;
	index = index < 0 ? index * (-1) : index;
	color_converter((uint32_t)g_data.img_matrix_td[index]);
	g_bitmap.buf[x * g_bitmap.width_in_pxl
		+ g_bitmap.col * 3 + 0] = g_rgb->b;
	g_bitmap.buf[x * g_bitmap.width_in_pxl
		+ g_bitmap.col * 3 + 1] = g_rgb->g;
	g_bitmap.buf[x * g_bitmap.width_in_pxl
		+ g_bitmap.col * 3 + 2] = g_rgb->r;
	free(g_rgb);
}

void	screen_init(unsigned char *header)
{
	g_bitmap.bit_per_pxl = 24;
	g_bitmap.width_in_pxl = ((g_file.window_w_td *
				g_bitmap.bit_per_pxl + 31) / 32) * 4;
	g_bitmap.image_size = g_bitmap.width_in_pxl * g_file.window_h_td;
	g_bitmap.info_header_size = 40;
	g_bitmap.bf_off_bits = 54;
	g_bitmap.file_size = 54 + g_bitmap.image_size;
	g_bitmap.biplanes = 1;
	ft_memcpy(header, "BM", 2);
	ft_memcpy(header + 2, &(g_bitmap.file_size), 4);
	ft_memcpy(header + 10, &(g_bitmap.bf_off_bits), 4);
	ft_memcpy(header + 14, &(g_bitmap.info_header_size), 4);
	ft_memcpy(header + 18, &(g_file.window_w_td), 4);
	ft_memcpy(header + 22, &(g_file.window_h_td), 4);
	ft_memcpy(header + 26, &(g_bitmap.biplanes), 2);
	ft_memcpy(header + 28, &(g_bitmap.bit_per_pxl), 2);
}

void	create_bmp_file(void)
{
	int				x;
	const char		*file_name = "screenshot.bmp";
	const int		len = 54;
	unsigned char	header[len];

	ft_memset(header, 0, len);
	screen_init(header);
	if (!(g_bitmap.buf = malloc((g_bitmap.image_size))))
		screenshot_error("failed to alloc the bitmap buffer !!");
	x = 0;
	g_bitmap.row = g_file.window_h_td - 1;
	while (g_bitmap.row-- >= 0)
	{
		g_bitmap.col = 0;
		while (g_bitmap.col++ < g_file.window_w_td)
			screen_data(x);
		x++;
	}
	g_bitmap.fd = open(file_name, O_WRONLY | O_CREAT);
	write(g_bitmap.fd, header, len);
	write(g_bitmap.fd, g_bitmap.buf, g_bitmap.image_size);
	close(g_bitmap.fd);
	free(g_bitmap.buf);
	exit_cub(EXIT_SUCCESS);
}
